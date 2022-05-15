/*
 * I2C bus driver for TI SM-USB-DIG
 *
 * Copyright (C) 2016 Texas Instruments Incorporated - http://www.ti.com/
 *	Andrew F. Davis <afd@ti.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether expressed or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 for more details.
 */

#include <linux/i2c.h>
#include <linux/mfd/ti-smusbdig.h>
#include <linux/module.h>
#include <linux/platform_device.h>

/* (data size - start condition - address - ACK) / ACK after data byte */
#define TI_SMUSBDIG_I2C_MAX_MSG ((TI_SMUSBDIG_DATA_SIZE - 3) / 2)

struct ti_smusbdig_i2c {
	struct device *dev;
	struct ti_smusbdig_device *ti_smusbdig;
	struct i2c_adapter adapter;
};

enum ti_smusbdig_i2c_command {
	TI_SMUSBDIG_I2C_START = 0x3,
	TI_SMUSBDIG_I2C_STOP = 0x4,
	TI_SMUSBDIG_I2C_ACKM = 0x5,
	TI_SMUSBDIG_I2C_ACKS = 0x6,
};

static ssize_t dut_show(struct device *dev,
				  struct device_attribute *attr, char *buf)
{

		return 0;
}

static ssize_t dut_store(struct device *dev,
				   struct device_attribute *attr,
				   const char *valbuf, size_t count)
{
        struct ti_smusbdig_i2c *ti_smusbdig_i2c = dev_get_drvdata(dev);
        u8 *buffer = kmalloc(TI_SMUSBDIG_PACKET_SIZE, GFP_KERNEL);
        int volt, ret;
	
        if (kstrtoint(valbuf, 10, &volt))
		    return -EINVAL;

        if (volt == 0) {
            buffer[0] = TI_SMUSBDIG_COMMAND;
//	        buffer[1] = TI_SMUSBDIG_SET_VOUT;
            buffer[1] = TI_SMUSBDIG_COMMAND_DUTPOWEROFF;
//	        buffer[2] = TI_SMUSBDIG_DUTOFF;
        ret = ti_smusbdig_xfer(ti_smusbdig_i2c->ti_smusbdig, buffer, 2);
		if (ret)
			return ret;
        }
        if (volt == 1) {
            buffer[0] = TI_SMUSBDIG_COMMAND;
	        buffer[1] = TI_SMUSBDIG_COMMAND_DUTPOWERON;
        ret = ti_smusbdig_xfer(ti_smusbdig_i2c->ti_smusbdig, buffer, 2);
		if (ret)
			return ret;
        }
        if (volt == 3) {
            buffer[0] = TI_SMUSBDIG_COMMAND;
	        buffer[1] = TI_SMUSBDIG_SET_VOUT;
	        buffer[2] = TI_SMUSBDIG_DUTOFF;
        ret = ti_smusbdig_xfer(ti_smusbdig_i2c->ti_smusbdig, buffer, 3);
		if (ret)
			return ret;
			
	        buffer[0] = TI_SMUSBDIG_COMMAND;
	        buffer[1] = TI_SMUSBDIG_SET_VOUT;
	        buffer[3] = TI_SMUSBDIG_VOUT3;
	    ret = ti_smusbdig_xfer(ti_smusbdig_i2c->ti_smusbdig, buffer, 3);
	    if (ret)
		    return ret;
         
            buffer[0] = TI_SMUSBDIG_COMMAND;
	        buffer[1] = TI_SMUSBDIG_COMMAND_DUTPOWERON;
        ret = ti_smusbdig_xfer(ti_smusbdig_i2c->ti_smusbdig, buffer, 2);
		if (ret)
			return ret;
		}	
        if (volt == 5) {
            buffer[0] = TI_SMUSBDIG_COMMAND;
	        buffer[1] = TI_SMUSBDIG_SET_VOUT;
	        buffer[2] = TI_SMUSBDIG_DUTOFF;
        ret = ti_smusbdig_xfer(ti_smusbdig_i2c->ti_smusbdig, buffer, 3);
		if (ret)
			return ret;
			
            buffer[0] = TI_SMUSBDIG_COMMAND;
	        buffer[1] = TI_SMUSBDIG_COMMAND_DUTPOWERON;
        ret = ti_smusbdig_xfer(ti_smusbdig_i2c->ti_smusbdig, buffer, 2);
		if (ret)
			return ret;
         }
         
	    kfree(buffer);
        return count;
}
static DEVICE_ATTR_RW(dut);

static int create_sysfs_attrs(struct i2c_adapter *adapter)
{
	int retval = 0;

			retval = device_create_file(&adapter->dev,
						    &dev_attr_dut);

	return retval;
}

static void remove_sysfs_attrs(struct i2c_adapter *adapter)
{

			device_remove_file(&adapter->dev, &dev_attr_dut);
}


static void ti_smusbdig_i2c_packet_init(struct ti_smusbdig_packet *packet)
{
	memset(packet, 0, sizeof(*packet));
	packet->function = TI_SMUSBDIG_I2C;
	packet->channel = 0x1;
}

static int ti_smusbdig_i2c_xfer(struct i2c_adapter *adapter,
				struct i2c_msg *msgs, int num)
{
	struct ti_smusbdig_i2c *ti_smusbdig_i2c = i2c_get_adapdata(adapter);
	struct ti_smusbdig_packet packet;
	int i, j, k, ret;
    
    
	for (i = 0; i < num; i++) {
		ti_smusbdig_i2c_packet_init(&packet);
		ti_smusbdig_packet_add_command(&packet, TI_SMUSBDIG_I2C_START);
		/* add read bit to address if needed */
		msgs[i].addr <<= 1;
		if (msgs[i].flags & I2C_M_RD)
			msgs[i].addr |= BIT(0);
		ti_smusbdig_packet_add_data(&packet, msgs[i].addr);
		ti_smusbdig_packet_add_command(&packet, TI_SMUSBDIG_I2C_ACKS);
		if (msgs[i].flags & I2C_M_RD) {
			for (j = 0; j < msgs[i].len; j++) {
				ti_smusbdig_packet_add_data(&packet, 0xff);
				ti_smusbdig_packet_add_command(&packet, TI_SMUSBDIG_I2C_ACKM);
			}
		} else {
			for (j = 0; j < msgs[i].len; j++) {
				ti_smusbdig_packet_add_data(&packet, msgs[i].buf[j]);
				ti_smusbdig_packet_add_command(&packet, TI_SMUSBDIG_I2C_ACKS);
			}
		}

		ret = ti_smusbdig_xfer(ti_smusbdig_i2c->ti_smusbdig,
				       (u8 *)&packet, sizeof(packet));
		if (ret)
			return ret;

		/*
		 * now we read in any data we got during read MSGs
		 * and check ACKS
		 */
		if (((u8 *)&packet)[2]) {
			num = -EPROTO;
			goto stop;
		}
		for (j = 0, k = 3; j < msgs[i].len; j++, k += 2) {
			if (msgs[i].flags & I2C_M_RD) {
				msgs[i].buf[j] = ((u8 *)&packet)[k];
			} else if (((u8 *)&packet)[k + 1]) {
				num = -EPROTO;
				goto stop;
			}
		}
	}

stop:
	/* send stop condition */
	ti_smusbdig_i2c_packet_init(&packet);
	ti_smusbdig_packet_add_command(&packet, TI_SMUSBDIG_I2C_STOP);
	ret = ti_smusbdig_xfer(ti_smusbdig_i2c->ti_smusbdig,
			       (u8 *)&packet, sizeof(packet));
	if (ret)
		return ret;
    
	return num;
}

static u32 ti_smusbdig_i2c_func(struct i2c_adapter *adapter)
{
	return I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
}

static const struct i2c_algorithm ti_smusbdig_i2c_algo = {
	.master_xfer = ti_smusbdig_i2c_xfer,
	.functionality = ti_smusbdig_i2c_func,
};

static struct i2c_adapter ti_smusbdig_i2c_adapter = {
	.owner = THIS_MODULE,
	.class = I2C_CLASS_HWMON,
	.algo = &ti_smusbdig_i2c_algo,
};

static struct i2c_adapter_quirks dln2_i2c_quirks = {
	.max_read_len = TI_SMUSBDIG_I2C_MAX_MSG,
	.max_write_len = TI_SMUSBDIG_I2C_MAX_MSG,
};

static int ti_smusbdig_i2c_probe(struct platform_device *pdev)
{
	struct ti_smusbdig_i2c *ti_smusbdig_i2c;
	struct device *dev = &pdev->dev;
	int ret;

	ti_smusbdig_i2c = devm_kzalloc(dev, sizeof(*ti_smusbdig_i2c), GFP_KERNEL);
	if (!ti_smusbdig_i2c)
		return -ENOMEM;

	ti_smusbdig_i2c->dev = dev;
	ti_smusbdig_i2c->ti_smusbdig = dev_get_drvdata(dev->parent);
	ti_smusbdig_i2c->adapter = ti_smusbdig_i2c_adapter;
	strlcpy(ti_smusbdig_i2c->adapter.name, dev_name(dev),
		sizeof(ti_smusbdig_i2c->adapter.name));
	ti_smusbdig_i2c->adapter.quirks = &dln2_i2c_quirks;
	ti_smusbdig_i2c->adapter.dev.parent = dev;
	ti_smusbdig_i2c->adapter.dev.of_node = dev->of_node;

	i2c_set_adapdata(&ti_smusbdig_i2c->adapter, ti_smusbdig_i2c);
	platform_set_drvdata(pdev, ti_smusbdig_i2c);

	ret = i2c_add_adapter(&ti_smusbdig_i2c->adapter);
	if (ret) {
		dev_err(dev, "unable to add I2C adapter\n");
		return ret;
	}
    
    create_sysfs_attrs(&ti_smusbdig_i2c->adapter);

	dev_info(dev, "TI SM-USB-DIG Added: I2C Bus\n");

	return 0;
}

static int ti_smusbdig_i2c_remove(struct platform_device *pdev)
{
	struct ti_smusbdig_i2c *ti_smusbdig_i2c = platform_get_drvdata(pdev);

	remove_sysfs_attrs(&ti_smusbdig_i2c->adapter);
	i2c_del_adapter(&ti_smusbdig_i2c->adapter);

	return 0;
}

static const struct platform_device_id ti_smusbdig_i2c_id_table[] = {
	{ "ti-sm-usb-dig-i2c", },
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(platform, ti_smusbdig_i2c_id_table);

static struct platform_driver ti_smusbdig_i2c_driver = {
	.driver = {
		.name = "ti-sm-usb-dig-i2c",
	},
	.probe = ti_smusbdig_i2c_probe,
	.remove = ti_smusbdig_i2c_remove,
	.id_table = ti_smusbdig_i2c_id_table,
};
module_platform_driver(ti_smusbdig_i2c_driver);

MODULE_AUTHOR("Andrew F. Davis <afd@ti.com>");
MODULE_DESCRIPTION("I2C bus driver for TI SM-USB-DIG interface adapter");
MODULE_LICENSE("GPL v2");
