#include <linux/kernel.h>
#include <linux/tty.h>
#include <linux/module.h>
#include <linux/usb.h>
#include <linux/usb/serial.h>
#include <linux/uaccess.h>
#include <linux/init.h>

//this code is inspired from wishbone serial driver in linux kernel
static const struct usb_device_id id_table[] = {
//       {USB_DEVICE(0x0483,
//                   0x374b)},
       {USB_DEVICE_AND_INTERFACE_INFO(0x0483, 0x374b, 0xA, 0x00, 0x00)},
//       {USB_DEVICE(0x0483, 0x374b)},
       {},
};

MODULE_DEVICE_TABLE(usb, id_table);

//this is called when i did sudo minicom
static int
_serial_open(struct tty_struct *tty,
             struct usb_serial_port *port)
{
   int retval;
   printk("device open\n");

   //send usb control msg to the device to notify that a new stream has begun
   retval = usb_serial_generic_open(tty, port);

   return retval;
}

//this is called when i closed `sudo minicom`
static void
_serial_close(struct usb_serial_port *port)
{
   usb_serial_generic_close(port);
   // send usb control msg to the device to notify that a stream has been stopped
   printk("device close\n");
}

static struct usb_serial_driver my_serial_device = {
     .driver = {
          .owner = THIS_MODULE,
          .name = "my_serial",
     },
     .id_table = id_table,
     .num_ports = 1,
     .open = _serial_open,
     .close = _serial_close,
};

static struct usb_serial_driver * const serial_drivers[] = {
     &my_serial_device, NULL
};

module_usb_serial_driver(serial_drivers, id_table);

MODULE_AUTHOR("Amitesh Singh");
MODULE_DESCRIPTION("simple serial driver");
MODULE_LICENSE("GPL");
