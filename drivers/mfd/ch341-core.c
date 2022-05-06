// SPDX-License-Identifier: GPL-2.0
/*
 * Core driver for the CH341A, CH341B and CH341T in I2C/SPI/GPIO
 * mode. There are cell drivers available for I2C and GPIO. SPI is not
 * yet supported.
 *
 * Copyright 2022, Frank Zago
 * Copyright (c) 2017 Gunar Schorcht (gunar@schorcht.net)
 * Copyright (c) 2016 Tse Lun Bien
 * Copyright (c) 2014 Marco Gittler
 * Copyright (c) 2006-2007 Till Harbaum (Till@Harbaum.org)
 */

#include <linux/kernel.h>
#include <linux/mfd/ch341.h>
#include <linux/mfd/core.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/usb.h>

static const struct mfd_cell ch341_devs[] = {
	{
		.name = "ch341-gpio",
	},
	{
		.name = "ch341-i2c",
	},
};

static int ch341_usb_probe(struct usb_interface *iface,
			   const struct usb_device_id *usb_id)
{
	struct usb_host_endpoint *endpoints;
	struct ch341_device *dev;
	int rc;

	dev = devm_kzalloc(&iface->dev, sizeof(*dev), GFP_KERNEL);
	if (!dev)
		return -ENOMEM;

	dev->usb_dev = usb_get_dev(interface_to_usbdev(iface));
	dev->iface = iface;
	mutex_init(&dev->usb_lock);

	if (iface->cur_altsetting->desc.bNumEndpoints != 3) {
		rc = -ENODEV;
		goto free_dev;
	}

	endpoints = iface->cur_altsetting->endpoint;
	if (!usb_endpoint_is_bulk_in(&endpoints[0].desc) ||
	    !usb_endpoint_is_bulk_out(&endpoints[1].desc) ||
	    !usb_endpoint_xfer_int(&endpoints[2].desc)) {
		rc = -ENODEV;
		goto free_dev;
	}

	dev->ep_in = endpoints[0].desc.bEndpointAddress;
	dev->ep_out = endpoints[1].desc.bEndpointAddress;
	dev->ep_intr = endpoints[2].desc.bEndpointAddress;
	dev->ep_intr_interval = endpoints[2].desc.bInterval;

	usb_set_intfdata(iface, dev);

	rc = mfd_add_hotplug_devices(&iface->dev, ch341_devs,
				     ARRAY_SIZE(ch341_devs));
	if (rc) {
		rc = dev_err_probe(&iface->dev, rc,
				   "Failed to add mfd devices to core\n");
		goto free_dev;
	}

	return 0;

free_dev:
	usb_put_dev(dev->usb_dev);

	return rc;
}

static void ch341_usb_disconnect(struct usb_interface *usb_if)
{
	struct ch341_device *dev = usb_get_intfdata(usb_if);

	mfd_remove_devices(&usb_if->dev);
	usb_put_dev(dev->usb_dev);
}

static const struct usb_device_id ch341_usb_table[] = {
	{ USB_DEVICE(0x1a86, 0x5512) },
	{ }
};
MODULE_DEVICE_TABLE(usb, ch341_usb_table);

static struct usb_driver ch341_usb_driver = {
	.name       = "ch341-mfd",
	.id_table   = ch341_usb_table,
	.probe      = ch341_usb_probe,
	.disconnect = ch341_usb_disconnect,
};
module_usb_driver(ch341_usb_driver);

MODULE_AUTHOR("Various");
MODULE_DESCRIPTION("CH341 USB to I2C/SPI/GPIO adapter");
MODULE_LICENSE("GPL");
