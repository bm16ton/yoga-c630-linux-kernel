#include <linux/init.h>// macros used to markup functions e.g. __init, __exit
#include <linux/module.h>// Core header for loading LKMs into the kernel
#include <linux/kernel.h>// Contains types, macros, functions for the kernel
#include <linux/device.h>// Header to support the kernel Driver Model

#include <linux/usb.h> //for usb stuffs
#include <linux/slab.h> //for

#include <linux/workqueue.h> //for work_struct
#include <linux/leds.h> //for led

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ben Maddocks");
MODULE_DESCRIPTION("Avr/stm32 led driver"); //sysfs
MODULE_VERSION("0.1"); //

//one structure for each connected device
struct my_usb
{
   struct usb_device *udev;
   struct work_struct work;
   struct led_classdev led;

};

#define MY_USB_VENDOR_ID 0x0483
#define MY_USB_PRODUCT_ID 0x5740
static struct usb_device_id my_usb_table[] = {
       { USB_DEVICE(MY_USB_VENDOR_ID, MY_USB_PRODUCT_ID) },
       {},
};

MODULE_DEVICE_TABLE(usb, my_usb_table);

//void *ret1 =  0;
static char ret2[0]; // = "0";
static int8_t ret5[] = "1";
static int8_t ret6[] = "2";
static int8_t ret7[] = "3";
static int8_t ret8[] = "9";
static int8_t ret3[] = "\n";
int test;


static void
usb_avr_led_work(struct work_struct *work)
{
   struct my_usb *sd = container_of(work, struct my_usb, work);
   int actual_len;
   int i;
   int ii;
   int iii;

  if (test == 9) {
	ii =	usb_bulk_msg(sd->udev, usb_sndbulkpipe(sd->udev, 1),
				   ret8, 1, &actual_len,
				   1000);

   if (!ii) {
   ;
   }
  }
   else {

    if (test > 9 && test < 20) {
	ii =	usb_bulk_msg(sd->udev, usb_sndbulkpipe(sd->udev, 1),
				   ret5, 1, &actual_len,
				   1000);


   if (!ii) {
    ;
   }
   
   }
    else if (test > 19 && test < 30) {
	ii =	usb_bulk_msg(sd->udev, usb_sndbulkpipe(sd->udev, 1),
				   ret6, 1, &actual_len,
				   1000);


   if (!ii) {
   ;
   }
   }
   else if (test > 29 && test < 39) {
	ii =	usb_bulk_msg(sd->udev, usb_sndbulkpipe(sd->udev, 1),
				   ret7, 1, &actual_len,
				   1000);


   if (!ii) {
    ;
   }
   
   }
   
   i =	usb_bulk_msg(sd->udev, usb_sndbulkpipe(sd->udev, 1),
				   ret2, 1, &actual_len,
				   1000);
				   
   if (!i) {
   ;
   }
   
  }
   
   iii =	usb_bulk_msg(sd->udev, usb_sndbulkpipe(sd->udev, 1),
				   ret3, 1, &actual_len,
				   1000);
     
     if (!iii) {
   ;
   }
}

static void
usb_avr_led_set(struct led_classdev *led,
                enum led_brightness brightness)
{
   struct my_usb *data = container_of(led, struct my_usb, led);

    test = brightness;
    if (brightness <= 8) {
   ret2[0] = brightness + 48;
   }
   if (brightness > 9 && brightness < 20) {
   ret2[0] = brightness + 38;
   }
   if (brightness > 19 && brightness < 30) {
   ret2[0] = brightness + 28;
   }
   if (brightness > 29 && brightness < 40) {
   ret2[0] = brightness + 18;
   }

   schedule_work(&data->work);
}

static int
my_usb_probe(struct usb_interface *interface,
             const struct usb_device_id *id)
{
   struct usb_device *udev = interface_to_usbdev(interface);
   struct usb_host_interface *iface_desc;
   struct usb_endpoint_descriptor *endpoint;
   struct my_usb *data;
   int i;

   printk(KERN_INFO "manufacturer: %s", udev->manufacturer);
   printk(KERN_INFO "product: %s", udev->product);

   iface_desc = interface->cur_altsetting;
   printk(KERN_INFO "vusb led %d probed: (%04X:%04X)",
          iface_desc->desc.bInterfaceNumber, id->idVendor, id->idProduct);
   printk(KERN_INFO "bNumEndpoints: %d", iface_desc->desc.bNumEndpoints);

   for (i = 0; i < iface_desc->desc.bNumEndpoints; i++)
     {

        endpoint = &iface_desc->endpoint[i].desc;
        if (endpoint->bEndpointAddress == 131) {
            return -ENODEV;
        }
        printk(KERN_INFO "ED[%d]->bEndpointAddress: 0x%02X\n",
               i, endpoint->bEndpointAddress);
        printk(KERN_INFO "ED[%d]->bmAttributes: 0x%02X\n",
               i, endpoint->bmAttributes);
        printk(KERN_INFO "ED[%d]->wMaxPacketSize: 0x%04X (%d)\n",
               i, endpoint->wMaxPacketSize, endpoint->wMaxPacketSize);
     }

   data = kzalloc(sizeof(struct my_usb), GFP_KERNEL);
   if (data == NULL)
     {
        //handle error
     }

   //increase ref count, make sure u call usb_put_dev() in disconnect()
   data->udev = usb_get_dev(udev);

   data->led.name = kasprintf(GFP_KERNEL, "%s-%s:w:stm32-led",
                              dev_driver_string(&data->udev->dev),
                              dev_name(&data->udev->dev));
   data->led.brightness_set = usb_avr_led_set;
   data->led.brightness = LED_OFF;
   data->led.max_brightness = 32;



   usb_set_intfdata(interface, data);

   printk(KERN_INFO "usb device is connected");

   INIT_WORK(&data->work, usb_avr_led_work);

   //register led device class
   led_classdev_register(&data->udev->dev, &data->led);

   return 0;
}

//called when unplugging a USB device
static void
my_usb_disconnect(struct usb_interface *interface)
{
   struct my_usb *data;

   data = usb_get_intfdata(interface);

   led_classdev_unregister(&data->led);
   cancel_work_sync(&data->work);

   usb_set_intfdata(interface, NULL);

   //deref the count
   usb_put_dev(data->udev);

   kfree(data); //deallocate, allocated by kzmalloc()

   printk(KERN_INFO "led usb device is disconnected");
}

static struct usb_driver my_usb_driver = {
     .name = "stm32-avr-led",
     .id_table = my_usb_table,
     .probe = my_usb_probe,
     .disconnect = my_usb_disconnect,
};


//we could use module_usb_driver(my_usb_driver); instead of
// init and exit functions
//called on module loading
static int __init
_usb_init(void)
{
   int result;
   printk(KERN_INFO "usb driver is loaded");

   result = usb_register(&my_usb_driver);
   if (result)
     {
        printk(KERN_ALERT "device registeration failed!!");
     }
   else
     {
        printk(KERN_INFO "device registered");
     }

   return result;
}

//called on module unloading
static void __exit
_usb_exit(void)
{
   printk(KERN_INFO "usb driver is unloaded");
   usb_deregister(&my_usb_driver);
}

module_init(_usb_init);
module_exit(_usb_exit);
