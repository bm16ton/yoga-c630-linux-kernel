/*
 * driver for the spi-tiny-usb adapter - 1.0
 *
 * Copyright (C) 2014 Krystian Duzynski (krystian.duzynski@gmail.com)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, version 2.
 *
 * Initially based on i2c-tiny-usb project of Till Harbaum (Till@Harbaum.org)
 */

#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/types.h>

#include <linux/usb.h>
#include <linux/gpio.h>
#include <linux/spi/spi.h>
#include <linux/uio_driver.h>
//16ton
#include <linux/delay.h>
#include <linux/iopoll.h>




#define USB_CMD_WRITE       0
#define USB_CMD_READ        1
#define USB_CMD_GPIO_OUTPUT 2
#define USB_CMD_GPIO_INPUT  3
#define USB_CMD_GPIO_SET    4
#define USB_CMD_GPIO_GET    5

#define FLAGS_BEGIN 1
#define FLAGS_END   2

#define VID 0x16c1
#define PID 0x06db

const char *gpio_names[] = { "led", "ext" };

/* Structure to hold all of our device specific stuff */
struct spi_tiny_usb {
	struct usb_device *usb_dev;	/* the usb device for this device */
	struct usb_interface *interface;	/* the interface for this device */
	struct urb *urb;	/* urb for usb interrupt transfer */
	char *urbBuffer;	/* urb incoming data buffer */
	struct spi_master *master;	/* spi master related things */
	struct spi_device *spidev;	/* spi device related things */
	struct spi_board_info info;	/* board info for spidev module */
	struct uio_info *uio;	/* Userspace IO for interrupt management */
	struct gpio_chip gpio_chip;	/* gpio related things */
};

static void spi_tiny_usb_free(struct spi_tiny_usb *priv)
{
	usb_put_dev(priv->usb_dev);
	kfree(priv);
}

static int spi_tiny_usb_freqtodiv(int freq)
{
	int div = 48 * 1000 * 1000 / freq;
	int i, divVal = 0;
	for (i = 2; i <= 256; i *= 2, divVal++)
		if (i >= div)
			break;
	return divVal;
}

static int
usb_read(struct spi_tiny_usb *dev, int cmd, int value, int index, void *data, int len);
static int
usb_write(struct spi_tiny_usb *dev, int cmd, int value, int index, void *data, int len);

/* ----- begin of spi layer ---------------------------------------------- */

static int spi_tiny_usb_xfer_one(struct spi_master *master, struct spi_message *m)
{
	struct spi_tiny_usb *priv = spi_master_get_devdata(master);
	struct spi_transfer *t;
	int spi_flags;
	int ret = 0;

	m->actual_length = 0;

	spi_flags = FLAGS_BEGIN;
	list_for_each_entry(t, &m->transfers, transfer_list) {
		if (list_is_last(&t->transfer_list, &m->transfers))
			spi_flags |= FLAGS_END;

		spi_flags |= spi_tiny_usb_freqtodiv(t->speed_hz) << 2;

		dev_dbg(&master->dev,
			"tx: %p rx: %p len: %d speed: %d flags: %d delay: %d\n", t->tx_buf,
			t->rx_buf, t->len, t->speed_hz, spi_flags, t->delay.value);

		if (t->cs_change)
			spi_flags |= FLAGS_END;

		if (t->tx_buf) {
			ret = usb_write(priv, 0, 0, spi_flags, (void *)t->tx_buf, t->len);
			if (ret < 0)
				break;
		} else {
			void *txbuf = kmalloc(t->len, GFP_KERNEL);
			memset(txbuf, 0x00, t->len);
			if (!txbuf) {
				ret = -ENOMEM;
				break;
			}
			ret = usb_write(priv, 0, 0, spi_flags, txbuf, t->len);
			kfree(txbuf);
			if (ret < 0)
				break;
		}

		if (t->rx_buf) {
			ret = usb_read(priv, 1, 0, 0, t->rx_buf, t->len);
			if (ret < 0)
				break;
		}
		// spin_lock_irqsave(&ebu_lock, flags);
		// ret = spi_tiny_usb_xfer(m->spi, t, spi_flags);
		// spin_unlock_irqrestore(&ebu_lock, flags);

		m->actual_length += t->len;

		if (t->delay.value)
			udelay(t->delay.value);

		spi_flags = 0;

		if (t->cs_change)
			spi_flags |= FLAGS_BEGIN;
	}

	m->status = ret;
	spi_finalize_current_message(master);

	return 0;
}

static int spi_tiny_usb_irqcontrol(struct uio_info *info, s32 irq_on)
{
	struct spi_tiny_usb *priv = (struct spi_tiny_usb *)info->priv;
	dev_dbg(&priv->interface->dev, "spi_tiny_usb_irqcontrol\n");
	return 0;
}

/* ----- end of spi layer ------------------------------------------------ */

/* ----- begin of gpio layer ---------------------------------------------- */

static inline struct spi_tiny_usb *spi_tiny_usb_gc_to_priv(struct gpio_chip *chip)
{
	return container_of(chip, struct spi_tiny_usb, gpio_chip);
}

static int spi_tiny_usb_gpio_input(struct gpio_chip *chip, unsigned offset)
{
	struct spi_tiny_usb *priv = spi_tiny_usb_gc_to_priv(chip);
	int ret;

	if (offset == 0)
		return -ENXIO;

	ret = usb_read(priv, USB_CMD_GPIO_INPUT, 0, offset, 0, 0);
	if (ret < 0)
		return ret;

	return 0;
}

static int spi_tiny_usb_gpio_get(struct gpio_chip *chip, unsigned offset)
{
	struct spi_tiny_usb *priv = spi_tiny_usb_gc_to_priv(chip);
	int ret, retval;

	char *rxbuf = kmalloc(1, GFP_KERNEL);
	if (!rxbuf)
		return -ENOMEM;
	ret = usb_read(priv, USB_CMD_GPIO_GET, 0, offset, rxbuf, 1);
	retval = rxbuf[0] ? 1 : 0;
	kfree(rxbuf);
	if (ret < 0)
		return ret;

	return retval;
}

static int spi_tiny_usb_gpio_output(struct gpio_chip *chip, unsigned offset, int val)
{
	struct spi_tiny_usb *priv = spi_tiny_usb_gc_to_priv(chip);
	int ret;

	ret = usb_read(priv, USB_CMD_GPIO_OUTPUT, 0, offset, 0, 0);
	if (ret < 0)
		return ret;

	return 0;
}

static void spi_tiny_usb_gpio_set(struct gpio_chip *chip, unsigned offset, int val)
{
	struct spi_tiny_usb *priv = spi_tiny_usb_gc_to_priv(chip);

	usb_read(priv, USB_CMD_GPIO_SET, val, offset, 0, 0);
}

/* ----- end of gpio layer ------------------------------------------------ */

/* ----- begin of usb layer ---------------------------------------------- */

static const struct usb_device_id spi_tiny_usb_table[] = {
	{USB_DEVICE(VID, PID)},
	{}
};

MODULE_DEVICE_TABLE(usb, spi_tiny_usb_table);

static void spi_tiny_usb_urb_complete(struct urb *urb)
{
	struct spi_tiny_usb *priv = (struct spi_tiny_usb *)urb->context;
	int ret;

	if (urb->status == 0) {
		uio_event_notify(priv->uio);
		dev_info(&priv->interface->dev,
			"spi_tiny_usb_urb_complete (%d) %d %d %d %d\n",
			urb->status, priv->urbBuffer[0], priv->urbBuffer[1],
			priv->urbBuffer[2], priv->urbBuffer[3]);
	}

	ret = usb_submit_urb(priv->urb, GFP_KERNEL);
}

static int
usb_read(struct spi_tiny_usb *dev, int cmd, int value, int index, void *data, int len)
{
	/* do control transfer */
	return usb_control_msg(dev->usb_dev, usb_rcvctrlpipe(dev->usb_dev, 0),
			       cmd,
			       USB_TYPE_VENDOR | USB_RECIP_INTERFACE |
			       USB_DIR_IN, value, index, data, len, 2000);
}

static int
usb_write(struct spi_tiny_usb *dev, int cmd, int value, int index, void *data, int len)
{
	/* do control transfer */
	return usb_control_msg(dev->usb_dev, usb_sndctrlpipe(dev->usb_dev, 0),
			       cmd, USB_TYPE_VENDOR | USB_RECIP_INTERFACE,
			       value, index, data, len, 2000);
}

static int spi_tiny_usb_probe(struct usb_interface *interface,
			      const struct usb_device_id *id)
{
	struct spi_tiny_usb *priv;
	int ret = -ENOMEM;
	u16 version;

	dev_dbg(&interface->dev, "probing usb device\n");

	/* allocate memory for our device state and initialize it */
	priv = kzalloc(sizeof(*priv), GFP_KERNEL);
	if (priv == NULL)
		return -ENOMEM;

	priv->usb_dev = usb_get_dev(interface_to_usbdev(interface));
	priv->interface = interface;

	/* save our data pointer in this interface device */
	usb_set_intfdata(interface, priv);

	version = le16_to_cpu(priv->usb_dev->descriptor.bcdDevice);
	dev_info(&interface->dev,
		 "version %x.%02x found at bus %03d address %03d\n",
		 version >> 8, version & 0xff, priv->usb_dev->bus->busnum,
		 priv->usb_dev->devnum);

	dev_info(&interface->dev, "connected spi-tiny-usb device\n");

	// SPI master
	priv->master = spi_alloc_master(&interface->dev, sizeof(*priv));
	if (!priv->master)
		goto error;
	priv->master->mode_bits = SPI_MODE_0;
	priv->master->flags = 0;
	// priv->master->setup = spi_tiny_usb_setup;
	// priv->master->prepare_transfer_hardware = spi_tiny_usb_prepare_xfer;
	priv->master->transfer_one_message = spi_tiny_usb_xfer_one;
	// priv->master->unprepare_transfer_hardware = spi_tiny_usb_unprepare_xfer;
	priv->master->dev.of_node = interface->dev.of_node;
	priv->master->num_chipselect = 1;
	priv->master->max_speed_hz = 48 * 1000 * 1000 / 2;
	priv->master->min_speed_hz = 48 * 1000 * 1000 / 256;
	// priv->master->dev.platform_data = priv;
	spi_master_set_devdata(priv->master, priv);

	ret = spi_register_master(priv->master);
	if (ret)
		goto error2;

	strcpy(priv->info.modalias, "spidev");
	priv->info.max_speed_hz = 48 * 1000 * 1000 / 2;
	priv->info.chip_select = 0;
	priv->info.mode = SPI_MODE_0;

	priv->info.controller_data = priv;
	priv->spidev = spi_new_device(priv->master, &priv->info);
	if (!priv->spidev)
		goto error2;
	dev_info(&interface->dev, "added new SPI device\n");

	// UIO
	priv->uio = kzalloc(sizeof(struct uio_info), GFP_KERNEL);
	if (!priv->uio)
		goto error2;
	priv->uio->priv = priv;
	priv->uio->name = "spi-tiny-usb";
	priv->uio->version = "1.0.16ton";

	priv->uio->mem[0].size = 0;
	priv->uio->port[0].size = 0;

	priv->uio->irq = UIO_IRQ_CUSTOM; //UIO_IRQ_CUSTOM;
	priv->uio->irq_flags = IRQF_SHARED;
	priv->uio->irqcontrol = spi_tiny_usb_irqcontrol;

	if (uio_register_device(&interface->dev, priv->uio))
		goto error2;
	dev_info(&interface->dev, "registered new UIO device\n");

	// USB interrupt
	priv->urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!priv->urb) {
	    dev_info(&interface->dev, "spi-tiny-usb no usb irq!\n");
		goto error2;
        };
    //16ton


	priv->urbBuffer = kmalloc(64, GFP_KERNEL);

	usb_fill_int_urb(priv->urb, priv->usb_dev,
			 usb_rcvintpipe(priv->usb_dev, 1), priv->urbBuffer, 64,
			 spi_tiny_usb_urb_complete, priv, 10);


	ret = usb_submit_urb(priv->urb, GFP_KERNEL);
	if (ret)
	    dev_info(&interface->dev, "spi-tiny-usb priv urb gfp_kernel failedr\n");
//		goto error2;
	dev_info(&interface->dev, "started USB interrupts handler\n");

	// GPIOs
	memset(&priv->gpio_chip, 0x00, sizeof(priv->gpio_chip));
	priv->gpio_chip.owner = THIS_MODULE;
	priv->gpio_chip.parent = &interface->dev;
	priv->gpio_chip.label = dev_name(priv->gpio_chip.parent);
	priv->gpio_chip.direction_input = spi_tiny_usb_gpio_input;
	priv->gpio_chip.direction_output = spi_tiny_usb_gpio_output;
	priv->gpio_chip.get = spi_tiny_usb_gpio_get;
	priv->gpio_chip.set = spi_tiny_usb_gpio_set;
	priv->gpio_chip.base = -1;
	priv->gpio_chip.ngpio = 2;
	priv->gpio_chip.names = gpio_names;

	dev_dbg(&interface->dev, "adding GPIO interface\n");
	ret = gpiochip_add(&priv->gpio_chip);
	if (ret) {
		printk(KERN_DEBUG "err %d\n", ret);
		goto error2;
	}
	dev_info(&interface->dev, "added GPIO interface\n");

	return 0;

 error2:
	printk(KERN_DEBUG "spi-tiny-usb error2\n");
	spi_master_put(priv->master);

 error:
	printk(KERN_DEBUG "spi-tiny-usb error\n");
	if (priv)
		spi_tiny_usb_free(priv);

	return ret;
}

static void spi_tiny_usb_disconnect(struct usb_interface *interface)
{
	struct spi_tiny_usb *priv = usb_get_intfdata(interface);
//	int i, ret;
    int i;

	for (i = priv->gpio_chip.base; i < priv->gpio_chip.base + priv->gpio_chip.ngpio;
	     i++) {
		gpio_free(i);
	}

	dev_dbg(&interface->dev, "gpiochip_remove\n");
//	ret = gpiochip_remove(&priv->gpio_chip);
    gpiochip_remove(&priv->gpio_chip);

	dev_dbg(&interface->dev, "usb_kill_urb\n");
	usb_kill_urb(priv->urb);

	dev_dbg(&interface->dev, "urbBuffer\n");
	if (priv->urbBuffer)
		kfree(priv->urbBuffer);

	dev_dbg(&interface->dev, "uio\n");
	if (priv->uio) {
		uio_unregister_device(priv->uio);
		kfree(priv->uio);
	}

	dev_dbg(&interface->dev, "usb_free_urb\n");
	if (priv->urb)
		usb_free_urb(priv->urb);

	dev_dbg(&interface->dev, "spi_unregister_master\n");
	spi_unregister_master(priv->master);

	dev_dbg(&interface->dev, "spi_tiny_usb_free\n");
	usb_set_intfdata(interface, NULL);
	spi_tiny_usb_free(priv);

	dev_dbg(&interface->dev, "disconnected\n");
}

static struct usb_driver spi_tiny_usb_driver = {
	.name = "spi-tiny-usb",
	.probe = spi_tiny_usb_probe,
	.disconnect = spi_tiny_usb_disconnect,
	.id_table = spi_tiny_usb_table,
};

module_usb_driver(spi_tiny_usb_driver);

/* ----- end of usb layer ------------------------------------------------ */

MODULE_AUTHOR("Krystian Duzynski <krystian.duzynski@gmail.com>");
MODULE_DESCRIPTION("spi-tiny-usb driver v1.0");
MODULE_LICENSE("GPL");
