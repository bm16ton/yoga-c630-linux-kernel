/*
 * MFD Core driver for TI SM-USB-DIG
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

#include <linux/mfd/core.h>
#include <linux/mfd/ti-smusbdig.h>
#include <linux/module.h>
#include <linux/usb.h>

#define TI_USB_VENDOR_ID                0x0451
#define TI_USB_DEVICE_ID_SM_USB_DIG     0x2f90

#define TI_SMUSBDIG_USB_TIMEOUT_MS      1000

struct ti_smusbdig_device {
	struct usb_device *usb_dev;
	struct usb_interface *interface;
	const struct usb_device_id	*usb_dev_id;
};

static int create_sysfs_attrs(struct usb_interface *interface);

static ssize_t dut_show(struct device *dev,
				  struct device_attribute *attr, char *buf)
{

		return 0;
}

int ti_smusbdig_xfer(struct ti_smusbdig_device *ti_smusbdig,
		     u8 *buffer, int size)
{
	struct device *dev = &ti_smusbdig->interface->dev;
	int actual_length, ret;
    uint8_t *buffer2 = kmalloc(TI_SMUSBDIG_PACKET_SIZE, GFP_KERNEL);

	if (!ti_smusbdig || !buffer2 || size <= 0) {
		printk ("failed check\n");
		return -EINVAL;
        }
        
    
    void *buffer3 = kmemdup(buffer, TI_SMUSBDIG_PACKET_SIZE, GFP_KERNEL);

    printk(KERN_NOTICE "xfer (%p)\n", buffer3);

	ret = usb_interrupt_msg(ti_smusbdig->usb_dev,
				usb_sndintpipe(ti_smusbdig->usb_dev, 1),
				buffer3, size, &actual_length,
				TI_SMUSBDIG_USB_TIMEOUT_MS);
				
	kfree(buffer3);
	if (ret) {
		dev_err(dev, "USB transaction failed\n");
		return ret;
	}

	ret = usb_interrupt_msg(ti_smusbdig->usb_dev,
				usb_rcvintpipe(ti_smusbdig->usb_dev, 1),
				buffer2, TI_SMUSBDIG_PACKET_SIZE, &actual_length,
				TI_SMUSBDIG_USB_TIMEOUT_MS);
	
	memcpy(buffer, buffer2, TI_SMUSBDIG_PACKET_SIZE);
	
	if (ret) {
		dev_err(dev, "USB transaction failed\n");
		return ret;
	}
    kfree(buffer2);
	return 0;
}
EXPORT_SYMBOL_GPL(ti_smusbdig_xfer);

static const struct mfd_cell ti_smusbdig_mfd_cells[] = {
	{ .name = "ti-sm-usb-dig-gpio", },
	{ .name = "ti-sm-usb-dig-i2c", },
	{ .name = "ti-sm-usb-dig-spi", },
	{ .name = "ti-sm-usb-dig-w1", },
};

static int ti_smusbdig_probe(struct usb_interface *interface,
			     const struct usb_device_id *usb_id)
{
	struct usb_host_interface *hostif = interface->cur_altsetting;
	struct device *dev = &interface->dev;
	struct ti_smusbdig_device *ti_smusbdig;

	u8 *buffer = kmalloc(TI_SMUSBDIG_PACKET_SIZE, GFP_KERNEL);
	int ret;

	if (hostif->desc.bInterfaceNumber != 0 ||
	    hostif->desc.bNumEndpoints < 2)
		return -ENODEV;

    create_sysfs_attrs(interface);
    
	ti_smusbdig = devm_kzalloc(dev, sizeof(*ti_smusbdig), GFP_KERNEL);
	if (!ti_smusbdig)
		return -ENOMEM;

	ti_smusbdig->usb_dev = usb_get_dev(interface_to_usbdev(interface));
	ti_smusbdig->interface = interface;
	usb_set_intfdata(interface, ti_smusbdig);
    
	buffer[0] = TI_SMUSBDIG_VERSION;
	ret = ti_smusbdig_xfer(ti_smusbdig, buffer, 1);
	if (ret)
		return ret;

	dev_info(dev, "TI SM-USB-DIG Version: %d.%02d Found\n",
		 buffer[0], buffer[1]);


	buffer[0] = TI_SMUSBDIG_COMMAND;
	buffer[1] = TI_SMUSBDIG_SET_VOUT;
	buffer[3] = TI_SMUSBDIG_VOUT3;
	ret = ti_smusbdig_xfer(ti_smusbdig, buffer, 3);
	if (ret)
		return ret;

	dev_set_drvdata(dev, ti_smusbdig);
	ret = mfd_add_hotplug_devices(dev, ti_smusbdig_mfd_cells,
				      ARRAY_SIZE(ti_smusbdig_mfd_cells));
	if (ret) {
		dev_err(dev, "unable to add MFD devices\n");
		return ret;
	}

    kfree(buffer);
	return 0;
}

static ssize_t dut_store(struct device *dev,
				   struct device_attribute *attr,
				   const char *valbuf, size_t count)
{
            struct ti_smusbdig_device *ti_smusbdig = dev_get_drvdata(dev);
            int volt, ret;
	        u8 *buffer = kmalloc(TI_SMUSBDIG_PACKET_SIZE, GFP_KERNEL);
        if (kstrtoint(valbuf, 10, &volt))
		    return -EINVAL;

        if (volt == 0) {
            buffer[0] = TI_SMUSBDIG_COMMAND;
	        buffer[1] = TI_SMUSBDIG_SET_VOUT;
	        buffer[2] = TI_SMUSBDIG_DUTOFF;
        ret = ti_smusbdig_xfer(ti_smusbdig, buffer, 3);
		if (ret)
			return ret;
        }
        if (volt == 1) {
            buffer[0] = TI_SMUSBDIG_COMMAND;
	        buffer[1] = TI_SMUSBDIG_COMMAND_DUTPOWERON;
        ret = ti_smusbdig_xfer(ti_smusbdig, buffer, 2);
		if (ret)
			return ret;
        }
        if (volt == 3) {
            buffer[0] = TI_SMUSBDIG_COMMAND;
	        buffer[1] = TI_SMUSBDIG_SET_VOUT;
	        buffer[2] = TI_SMUSBDIG_DUTOFF;
        ret = ti_smusbdig_xfer(ti_smusbdig, buffer, 3);
		if (ret)
			return ret;
			
	        buffer[0] = TI_SMUSBDIG_COMMAND;
	        buffer[1] = TI_SMUSBDIG_SET_VOUT;
	        buffer[3] = TI_SMUSBDIG_VOUT3;
	    ret = ti_smusbdig_xfer(ti_smusbdig, buffer, 3);
	    if (ret)
		    return ret;
         
            buffer[0] = TI_SMUSBDIG_COMMAND;
	        buffer[1] = TI_SMUSBDIG_COMMAND_DUTPOWERON;
        ret = ti_smusbdig_xfer(ti_smusbdig, buffer, 2);
		if (ret)
			return ret;
		}	
        if (volt == 5) {
            buffer[0] = TI_SMUSBDIG_COMMAND;
	        buffer[1] = TI_SMUSBDIG_SET_VOUT;
	        buffer[2] = TI_SMUSBDIG_DUTOFF;
        ret = ti_smusbdig_xfer(ti_smusbdig, buffer, 3);
		if (ret)
			return ret;
			
            buffer[0] = TI_SMUSBDIG_COMMAND;
	        buffer[1] = TI_SMUSBDIG_COMMAND_DUTPOWERON;
        ret = ti_smusbdig_xfer(ti_smusbdig, buffer, 2);
		if (ret)
			return ret;
         }	   
         
	     kfree(buffer);
        return count;
}
static DEVICE_ATTR_RW(dut);

static int create_sysfs_attrs(struct usb_interface *interface)
{
	int retval = 0;

			retval = device_create_file(&interface->dev,
						    &dev_attr_dut);

	return retval;
}

static void remove_sysfs_attrs(struct usb_interface *interface)
{

			device_remove_file(&interface->dev, &dev_attr_dut);
}


static void ti_smusbdig_disconnect(struct usb_interface *interface)
{
	mfd_remove_devices(&interface->dev);
	remove_sysfs_attrs(interface);
}

static const struct usb_device_id ti_smusbdig_id_table[] = {
	{ USB_DEVICE(TI_USB_VENDOR_ID, TI_USB_DEVICE_ID_SM_USB_DIG) },
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(usb, ti_smusbdig_id_table);

static struct usb_driver ti_smusbdig_driver = {
	.name = "ti-sm-usb-dig",
	.probe = ti_smusbdig_probe,
	.disconnect = ti_smusbdig_disconnect,
	.id_table = ti_smusbdig_id_table,
};
module_usb_driver(ti_smusbdig_driver);

MODULE_AUTHOR("Andrew F. Davis <afd@ti.com>");
MODULE_DESCRIPTION("Core driver for TI SM-USB-DIG interface adapter");
MODULE_LICENSE("GPL v2");
