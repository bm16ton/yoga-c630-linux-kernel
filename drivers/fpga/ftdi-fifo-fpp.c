// SPDX-License-Identifier: GPL-2.0
/*
 * Altera FPGA firmware upload via FPP using FT232H Bitbang/FT245-FIFO.
 *
 * Copyright (C) 2017 - 2018 DENX Software Engineering
 * Anatolij Gustschin <agust@denx.de>
 */

#include <linux/bitops.h>
#include <linux/delay.h>
#include <linux/fpga/fpga-mgr.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sizes.h>
#include <linux/slab.h>
#include <linux/gpio/consumer.h>
#include <linux/platform_device.h>
#include <linux/usb.h>
#include <linux/usb/ft232h-intf.h>

#define BULK_OUT_BUF_SZ	SZ_1M
#define MAX_RETRIES	10

/*
 * With logic of CPLD we can write the state of nConfig pin and
 * read back the state of some pins (conf_done, init_done, nStatus).
 * Status header and bit assignment in data register on CPLD.
 */
#define INPUT_HEADER_0	0xA5
#define INPUT_HEADER_1	0x5A
#define IN_CONF_DONE	BIT(0)
#define IN_INIT_DONE	BIT(1)
#define IN_ADDR_SELECT	BIT(4)
#define IN_BOARD_REV	BIT(5)
#define OUT_NCONFIG	BIT(0)
#define OUT_RESET_N	BIT(1)

enum fpp_board_rev {
	BOARD_REVA = 1,
	BOARD_REVB = 2,
};

enum fpp_addr_sel {
	ADDR_SELECT_INVALID,
	ADDR_SELECT_GND,
	ADDR_SELECT_NC
};

struct fpp_mgr_ops {
	int (*write_init)(struct fpga_manager *mgr,
			  struct fpga_image_info *info,
			  const char *buf, size_t count);
	int (*write)(struct fpga_manager *mgr, const char *buf, size_t count);
	int (*write_complete)(struct fpga_manager *mgr,
			      struct fpga_image_info *info);
};

struct fpp_fpga_mgr_priv {
	struct platform_device		*pdev;
	struct usb_interface		*intf;
	const struct ft232h_intf_ops	*iops;
	struct fpga_manager	*mgr;
	struct fpp_mgr_ops	*ops;
	struct gpio_desc	*nconfig;
	struct gpio_desc	*conf_done;
	char			cfg_mode[8];
	u8			out_data_port;
	int			index;
	void			*bulk_buf;
	char			usb_dev_id[32];
	char			fpga_mgr_name[64];
	enum fpp_board_rev	rev;
	enum fpp_addr_sel	addr_sel;
};

static int fpp_fpga_mgr_set_data_port(struct fpp_fpga_mgr_priv *priv,
				      u8 bitmask, u8 value)
{
	struct device *dev = &priv->pdev->dev;
	struct bulk_desc desc;
	u8 *data;
	int ret;

	/*
	 * With CPLD connected (in FT245 FIFO mode) we use ACBUS8&9
	 * pins to switch between data and command mode:
	 * ACBUS8&9 == 0, 0  --> normal mode (data communication)
	 * ACBUS8&9 == 1, 0  --> command mode
	 */
	gpiod_set_raw_value_cansleep(priv->nconfig, 1);
	gpiod_set_raw_value_cansleep(priv->conf_done, 0);
	msleep(50);

	/* Write commands to CPLD */
	ret = priv->iops->set_bitmode(priv->intf, 0x00, BITMODE_SYNCFF);
	if (ret)
		return ret;

	if (value)
		priv->out_data_port |= bitmask;
	else
		priv->out_data_port &= ~bitmask;

	data = priv->bulk_buf;
	*data = priv->out_data_port;

	desc.dir_out = true;
	desc.act_len = 0;
	desc.len = 1;
	desc.data = data;
	desc.timeout = FTDI_USB_WRITE_TIMEOUT;

	ret = priv->iops->bulk_xfer(priv->intf, &desc);
	if (ret) {
		dev_err(dev, "Writing in SYNCFF mode failed: %d\n", ret);
		return ret;
	}

	msleep(50);
	/* Switch back to data mode with ACBUS8&9 back to low */
	gpiod_set_raw_value_cansleep(priv->nconfig, 0);
	gpiod_set_raw_value_cansleep(priv->conf_done, 0);
	msleep(50);

	return 0;
}

static int fpp_fpga_mgr_bitbang_write_init(struct fpga_manager *mgr,
					   struct fpga_image_info *info,
					   const char *buf, size_t count)
{
	struct fpp_fpga_mgr_priv *priv = mgr->priv;
	struct device *dev = &priv->pdev->dev;
	int retries = MAX_RETRIES;
	int ret;

	gpiod_set_value_cansleep(priv->nconfig, 0);
	msleep(50);
	gpiod_set_value_cansleep(priv->nconfig, 1);
	msleep(50);
	gpiod_set_value_cansleep(priv->nconfig, 0);

	/* Wait for CONF_DONE to get low */
	do {
		msleep(50);

		ret = gpiod_get_value_cansleep(priv->conf_done);
		if (ret < 0) {
			dev_err(dev, "Failed to get CONF_DONE pin: %d\n", ret);
			return ret;
		}

		if (!ret)
			break;
	} while (--retries > 0);

	if (!retries) {
		dev_warn(dev, "CONF_DONE low wait timeout\n");
		return -ETIMEDOUT;
	}

	ret = priv->iops->set_bitmode(priv->intf, 0xff, BITMODE_BITBANG);
	if (ret < 0)
		return ret;

	/* Set max. working baud rate (for hardware without CPLD) */
	return priv->iops->set_baudrate(priv->intf, 700000);
}

static int fpp_fpga_mgr_bitbang_write(struct fpga_manager *mgr,
				      const char *buf, size_t count)
{
	struct fpp_fpga_mgr_priv *priv = mgr->priv;
	struct bulk_desc desc;
	size_t blk_sz;
	int ret;

	desc.data = priv->bulk_buf;
	desc.dir_out = true;
	desc.timeout = FTDI_USB_WRITE_TIMEOUT;

	while (count) {
		blk_sz = min_t(size_t, count, BULK_OUT_BUF_SZ);
		memcpy(priv->bulk_buf, buf, blk_sz);
		desc.act_len = 0;
		desc.len = blk_sz;
		ret = priv->iops->bulk_xfer(priv->intf, &desc);
		if (ret < 0)
			return ret;

		buf += desc.act_len;
		count -= desc.act_len;
	}

	return 0;
}

static int fpp_fpga_mgr_bitbang_write_complete(struct fpga_manager *mgr,
					       struct fpga_image_info *info)
{
	struct fpp_fpga_mgr_priv *priv = mgr->priv;
	struct device *dev = &priv->pdev->dev;
	int retries = MAX_RETRIES;
	int ret;

	/* Wait for CONF_DONE to get high */
	do {
		msleep(50);

		ret = gpiod_get_value_cansleep(priv->conf_done);
		if (ret < 0)
			return ret;

		if (ret)
			break;
	} while (--retries > 0);

	if (!retries) {
		dev_warn(dev, "CONF_DONE wait timeout\n");
		return -ETIMEDOUT;
	}

	priv->iops->disable_bitbang(priv->intf);
	return 0;
}

static inline bool status_hdr_is_valid(u8 *buf)
{
	return buf[0] == INPUT_HEADER_0 && buf[1] == INPUT_HEADER_1;
}

static int fpp_fpga_mgr_read_status(struct fpp_fpga_mgr_priv *priv, u8 *status)
{
	struct device *dev = &priv->pdev->dev;
	u8 *inbuf = priv->bulk_buf;
	int retries = MAX_RETRIES;
	int ret;

	if (!status)
		return -EINVAL;

	/* Wait until CPLD sends valid header and status register */
	do {
		ret = priv->iops->read_data(priv->intf, inbuf, 64);
		if (ret < 0) {
			dev_err(dev, "Can't read status data: %d\n", ret);
			return ret;
		}

		/* Check input buffer header */
		if (ret >= 4 && status_hdr_is_valid(inbuf)) {
			*status = inbuf[2];
			return 0;
		}

		/* Wait and read back status again */
		msleep(100); /* CPLD sends status every 100ms */
	} while (--retries > 0);

	dev_warn(dev, "Timeout when reading status\n");
	return -ETIMEDOUT;
}

static int fpp_fpga_mgr_ft245_fifo_write_init(struct fpga_manager *mgr,
					      struct fpga_image_info *info,
					      const char *buf, size_t count)
{
	struct fpp_fpga_mgr_priv *priv = mgr->priv;
	struct device *dev = &priv->pdev->dev;
	int retries = MAX_RETRIES;
	int ret;
	u8 status;

	gpiod_direction_output_raw(priv->conf_done, 0);

	/* Set/reset nConfig via commands to CPLD */
	ret = fpp_fpga_mgr_set_data_port(priv, OUT_NCONFIG, 1);
	if (ret)
		return ret;
	ret = fpp_fpga_mgr_set_data_port(priv, OUT_NCONFIG, 0);
	if (ret)
		return ret;
	ret = fpp_fpga_mgr_set_data_port(priv, OUT_NCONFIG, 1);
	if (ret)
		return ret;

	/* In FT245 FIFO mode we need sync FIFO mode to talk to FPGA */
	ret = priv->iops->set_bitmode(priv->intf, 0xff, BITMODE_SYNCFF);
	if (ret)
		return ret;

	/* Wait until FPGA is ready for loading (conf_done zero) or timeout */
	do {
		ret = fpp_fpga_mgr_read_status(priv, &status);
		if (!ret) {
			/* Check conf_done status */
			if ((status & IN_CONF_DONE) == 0)
				break;
		}
	} while (--retries > 0);

	if (!retries) {
		dev_warn(dev, "CONF_DONE wait timeout\n");
		return -ETIMEDOUT;
	}

	/* Configure for max. baud rate (3MHz * 4 in bitbang mode) */
	return priv->iops->set_baudrate(priv->intf, 3000000);
}

static int fpp_fpga_mgr_ft245_fifo_write(struct fpga_manager *mgr,
					 const char *buf, size_t count)
{
	return fpp_fpga_mgr_bitbang_write(mgr, buf, count);
}

static int fpp_fpga_mgr_ft245_fifo_write_complete(struct fpga_manager *mgr,
						  struct fpga_image_info *info)
{
	struct fpp_fpga_mgr_priv *priv = mgr->priv;
	struct device *dev = &priv->pdev->dev;
	int retries = MAX_RETRIES;
	int ret;
	u8 mask, status;

	mask = IN_CONF_DONE | IN_INIT_DONE;

	do {
		ret = fpp_fpga_mgr_read_status(priv, &status);
		if (!ret) {
			/* Check conf_done/init_done status */
			if ((status & mask) == mask)
				break;
		}
	} while (--retries > 0);

	if (!retries) {
		dev_warn(dev, "INIT_DONE wait timeout\n");
		return -ETIMEDOUT;
	}

	/* Release Reset_n, keep nCONFIG high, too! */
	return fpp_fpga_mgr_set_data_port(priv, OUT_NCONFIG | OUT_RESET_N, 1);
}

static enum fpga_mgr_states fpp_fpga_mgr_state(struct fpga_manager *mgr)
{
	return FPGA_MGR_STATE_UNKNOWN;
}

static int fpp_fpga_mgr_write_init(struct fpga_manager *mgr,
				   struct fpga_image_info *info,
				   const char *buf, size_t count)
{
	struct fpp_fpga_mgr_priv *priv = mgr->priv;

	if (info && info->flags & FPGA_MGR_PARTIAL_RECONFIG) {
		dev_err(&mgr->dev, "Partial reconfiguration not supported.\n");
		return -EINVAL;
	}

	if (priv->ops->write_init)
		return priv->ops->write_init(mgr, info, buf, count);

	return -ENODEV;
}

static int fpp_fpga_mgr_write(struct fpga_manager *mgr, const char *buf,
			      size_t count)
{
	struct fpp_fpga_mgr_priv *priv = mgr->priv;

	if (priv->ops->write)
		return priv->ops->write(mgr, buf, count);

	return -ENODEV;
}

static int fpp_fpga_mgr_write_complete(struct fpga_manager *mgr,
				       struct fpga_image_info *info)
{
	struct fpp_fpga_mgr_priv *priv = mgr->priv;

	if (priv->ops->write_complete)
		return priv->ops->write_complete(mgr, info);

	return -ENODEV;
}

static struct fpp_mgr_ops fpp_mgr_bitbang_ops = {
	.write_init	= fpp_fpga_mgr_bitbang_write_init,
	.write		= fpp_fpga_mgr_bitbang_write,
	.write_complete	= fpp_fpga_mgr_bitbang_write_complete,
};

static struct fpp_mgr_ops fpp_mgr_ft245_fifo_ops = {
	.write_init	= fpp_fpga_mgr_ft245_fifo_write_init,
	.write		= fpp_fpga_mgr_ft245_fifo_write,
	.write_complete	= fpp_fpga_mgr_ft245_fifo_write_complete,
};

static const struct fpga_manager_ops fpp_fpga_mgr_ops = {
	.state		= fpp_fpga_mgr_state,
	.write_init	= fpp_fpga_mgr_write_init,
	.write		= fpp_fpga_mgr_write,
	.write_complete	= fpp_fpga_mgr_write_complete,
};

static ssize_t cfg_mode_show(struct device *dev, struct device_attribute *attr,
			     char *buf)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct fpga_manager *mgr = platform_get_drvdata(pdev);
	struct fpp_fpga_mgr_priv *priv = mgr->priv;

	return snprintf(buf, PAGE_SIZE, "%s\n", priv->cfg_mode);
}

static ssize_t cfg_mode_store(struct device *dev, struct device_attribute *attr,
			      const char *buf, size_t count)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct fpga_manager *mgr = platform_get_drvdata(pdev);
	struct fpp_fpga_mgr_priv *priv = mgr->priv;

	if (!count || count > sizeof(priv->cfg_mode))
		return -EINVAL;

	if (!strncmp(buf, "fifo", 4)) {
		strncpy(priv->cfg_mode, buf, sizeof(priv->cfg_mode) - 1);
		priv->cfg_mode[4] = 0;
		priv->ops = &fpp_mgr_ft245_fifo_ops;
		gpiod_direction_output_raw(priv->conf_done, 0);
	} else if (!strncmp(buf, "bitbang", 7)) {
		strncpy(priv->cfg_mode, buf, sizeof(priv->cfg_mode) - 1);
		priv->cfg_mode[7] = 0;
		priv->ops = &fpp_mgr_bitbang_ops;
		gpiod_direction_input(priv->conf_done);
	} else {
		return -EINVAL;
	}

	return count;
}

static DEVICE_ATTR_RW(cfg_mode);

static int fpp_fpga_mgr_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct fpp_fpga_mgr_priv *priv;
	struct fpga_manager *mgr;
	struct fifo_fpp_mgr_platform_data *pd;
	struct fpga_manager_info info = { 0 };
	int ret, retries = MAX_RETRIES;
	char id_string[8];
	u8 status = 0;

	pd = dev->platform_data;
	if (!pd) {
		dev_err(dev, "Missing platform data.\n");
		return -EINVAL;
	}

	if (!pd->ops ||
	    !pd->ops->bulk_xfer || !pd->ops->ctrl_xfer ||
	    !pd->ops->read_data || !pd->ops->write_data ||
	    !pd->ops->set_bitmode || !pd->ops->set_baudrate ||
	    !pd->ops->disable_bitbang)
		return -EINVAL;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->intf = to_usb_interface(dev->parent);
	priv->iops = pd->ops;

	ret = sscanf(dev_name(dev->parent), "%s", priv->usb_dev_id);
	if (ret != 1) {
		dev_err(dev, "Can't get parent device name: %d\n", ret);
		return -ENODEV;
	}

	priv->pdev = pdev;
	priv->ops = &fpp_mgr_ft245_fifo_ops;
	strncpy(priv->cfg_mode, "fifo", sizeof(priv->cfg_mode));

	priv->nconfig = devm_gpiod_get(dev, "nconfig", GPIOD_OUT_LOW);
	if (IS_ERR(priv->nconfig)) {
		ret = PTR_ERR(priv->nconfig);
		dev_err(dev, "Failed to get nconfig gpio: %d\n", ret);
		return ret;
	}

	priv->conf_done = devm_gpiod_get(dev, "conf_done", GPIOD_OUT_LOW);
	if (IS_ERR(priv->conf_done)) {
		ret = PTR_ERR(priv->conf_done);
		dev_err(dev, "Failed to get conf_done gpio: %d\n", ret);
		goto err_cfg1;
	}

	priv->bulk_buf = devm_kmalloc(dev, BULK_OUT_BUF_SZ,
				      GFP_KERNEL | GFP_DMA32);
	if (!priv->bulk_buf) {
		ret = -ENOMEM;
		goto err_cfg2;
	}

	ret = priv->iops->set_bitmode(priv->intf, 0xff, BITMODE_SYNCFF);
	if (ret)
		goto err_cfg2;

	/* Read status register from CPLD */
	do {
		ret = fpp_fpga_mgr_read_status(priv, &status);
		if (!ret)
			break;
	} while (--retries > 0);

	if (!retries) {
		ret = -ETIMEDOUT;
		goto err_cfg2;
	}

	priv->rev = (status & IN_BOARD_REV) ? BOARD_REVB : BOARD_REVA;

	if (priv->rev == BOARD_REVB) {
		priv->addr_sel = (status & IN_ADDR_SELECT) ?
				 ADDR_SELECT_NC : ADDR_SELECT_GND;
		if (priv->addr_sel == ADDR_SELECT_NC)
			strncpy(id_string, "right", sizeof(id_string));
		else
			strncpy(id_string, "left", sizeof(id_string));
	} else {
		priv->addr_sel = ADDR_SELECT_INVALID;
		strncpy(id_string, "single", sizeof(id_string));
	}

	dev_info(dev, "Board Rev %d, Addr Sel %d\n", priv->rev, priv->addr_sel);

	/* Use unique board ID and USB bus/port in FPGA manager name */
	snprintf(priv->fpga_mgr_name, sizeof(priv->fpga_mgr_name),
		 "ftdi-fpp-fpga-mgr %s %s", id_string, priv->usb_dev_id);

//	mgr = devm_fpga_mgr_create(dev, priv->fpga_mgr_name,
//				   &fpp_fpga_mgr_ops, priv);
//	if (!mgr)
//		goto err_cfg2;


	info.name = "ftdi fifo fpp";
	info.mops = &fpp_fpga_mgr_ops;
	info.priv = priv;
	info.compat_id = devm_kzalloc(dev, sizeof(priv->usb_dev_id), GFP_KERNEL);
	if (!info.compat_id)
		return -ENOMEM;

//	fme_mgr_get_compat_id(priv->ioaddr, info.compat_id);
	mgr = devm_fpga_mgr_register_full(dev, &info);
//	platform_set_drvdata(pdev, mgr);

//	ret = fpga_mgr_register(mgr);
//	if (ret) {
//		dev_err(dev, "unable to register FPGA manager\n");
//		goto err_cfg2;
//	}

	ret = device_create_file(dev, &dev_attr_cfg_mode);
	if (ret)
		dev_warn(dev, "Can't create cfg_mode interface %d\n", ret);

	return 0;

err_cfg2:
	devm_gpiod_put(dev, priv->conf_done);
err_cfg1:
	devm_gpiod_put(dev, priv->nconfig);
	return ret;
}

static int fpp_fpga_mgr_remove(struct platform_device *pdev)
{
	struct fpga_manager *mgr = platform_get_drvdata(pdev);
	struct fpp_fpga_mgr_priv *priv = mgr->priv;

	device_remove_file(&pdev->dev, &dev_attr_cfg_mode);
	fpga_mgr_unregister(mgr);
	devm_gpiod_put(&pdev->dev, priv->conf_done);
	devm_gpiod_put(&pdev->dev, priv->nconfig);
	return 0;
}

static struct platform_driver fpp_fpga_mgr_driver = {
	.driver.name	= "ftdi-fifo-fpp-mgr",
	.probe		= fpp_fpga_mgr_probe,
	.remove		= fpp_fpga_mgr_remove,
};

module_platform_driver(fpp_fpga_mgr_driver);

MODULE_ALIAS("platform:ftdi-fifo-fpp-mgr");
MODULE_AUTHOR("Anatolij Gustschin <agust@denx.de>");
MODULE_DESCRIPTION("FT232H Bitbang/FT245-FIFO FPP FPGA Manager Driver");
MODULE_LICENSE("GPL v2");
