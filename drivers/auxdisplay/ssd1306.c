// SPDX-License-Identifier: GPL-2.0
#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>         // Header to support the kernel Driver Model
#include <linux/kernel.h>         // Contains types, macros, functions for the kernel
#include <linux/fs.h>             // Header for the Linux file system support
#include <linux/uaccess.h>          // Required for the copy to user function
#include <linux/i2c.h>
#include <linux/delay.h>
#include "ssd1306.h"

struct i2c_client *ssd1306_i2c;

static int    majorNumber;                  ///< Stores the device number -- determined automatically
static char   message[4096] = {0};           ///< Memory for the string that is passed from userspace
static int    numberOpens = 0;              ///< Counts the number of times the device is opened
static struct class*  ssd1306Class  = NULL; ///< The device-driver class struct pointer
static struct device* ssd1306Device = NULL; ///< The device-driver device struct pointer

/**********************************************************************/
/*                  Funciones propias del Driver                      */
/**********************************************************************/

static void sentCommandSSD1306( uint8_t ssd1306Command )
{
    uint8_t i2cCommand = 0x00;   // Co = 0, D/C = 0
    i2c_smbus_write_i2c_block_data( ssd1306_i2c , i2cCommand, 1, &ssd1306Command);
}

// Direcciona en 0,0
static void homeDisplaySSD1306( void )
{
    char initSec[]  = {0x00, 0x21, 0x00, 0x7F, 0x22, 0x00, 0x07};
    i2c_master_send( ssd1306_i2c , initSec, sizeof(initSec) );
}

static void clearDisplaySSD1306( void )
{
    uint8_t idy, idx;
    uint8_t command = 0x40;   // Co = 0, D/C = 1
    char values[]   = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    homeDisplaySSD1306();

    for( idy = 0 ; idy < _SSD1306_LCD_HEIGHT_ / 8 ; idy++ )
        for( idx = 0 ; idx < _SSD1306_LCD_WIDTH_ / 8 ; idx++ )
            i2c_smbus_write_i2c_block_data( ssd1306_i2c , command , sizeof(values) , values );
}

static void clearPageSSD1306( uint8_t pageNum )
{
    uint8_t idx;
    uint8_t command = 0x40;   // Co = 0, D/C = 1
    char values[]   = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    if( pageNum  < 8)
    {
        homeDisplaySSD1306();
        sentCommandSSD1306( _SSD1306_PAGE_SET_ | pageNum );
        for( idx = 0 ; idx < _SSD1306_LCD_WIDTH_ / 8 ; idx++ )
            i2c_smbus_write_i2c_block_data( ssd1306_i2c , command, sizeof(values), values);
    }
}

static void setPageSSD1306( uint8_t pageNum )
{
    if( pageNum  < 8){
        homeDisplaySSD1306();
        sentCommandSSD1306( _SSD1306_PAGE_SET_ | pageNum );
    }
}

static void sentCharSSD1306( char letra )
{
	int idx;
    uint8_t i2cCommand = 0x40;   // Co = 0, D/C = 1
    char values[8] = {0x00, 0xff, 0x81, 0x81, 0x81, 0x81, 0xff, 0x00};  // []

    if( letra < 128)
    {
	    for( idx=0; idx<8 ; idx++ )
		    values[ idx ] = font16x16[ letra*8 + idx ];
    }

    i2c_smbus_write_i2c_block_data( ssd1306_i2c , i2cCommand, sizeof(values), values);
}

static void sentStringSSD1306( char *msg , uint32_t length )
{
	int idx;

    for( idx=0 ; idx < length ; idx++ )
        sentCharSSD1306( msg[idx]);
}

static void sentImgSSD1306( uint8_t *img )
{
    int idx, idy;
    uint8_t i2cCommand = 0x40;   // Co = 0, D/C = 1
    char values[ _I2C_BUFFER_MAX_ ];

    homeDisplaySSD1306();

	for( idx=0 ; idx < 1024 ; idx=idx+_I2C_BUFFER_MAX_ )
	{
		for ( idy=0 ; idy < _I2C_BUFFER_MAX_ ; idy++)
			values[ idy ] = img[ idx + idy ];

    	i2c_smbus_write_i2c_block_data( ssd1306_i2c , i2cCommand, sizeof(values), values);
	}
}

/***********************************************************
 * Char device definitions
 ***********************************************************
*/

static struct file_operations fops =
{
    .open =             ssd1306_open,
    .write =            ssd1306_write,
    .release =          ssd1306_release,
    .unlocked_ioctl	=   ssd1306_ioctl,
};

static int ssd1306_open(struct inode *inodep, struct file *filep){
    // numberOpens++;
    // printk(KERN_INFO "ssd1306: Device has been opened %d time(s)\n", numberOpens);
    if( 0 == numberOpens++ )
    {
        clearDisplaySSD1306();
        homeDisplaySSD1306();
        sentCommandSSD1306( _SSD1306_NORMALDISPLAY_);
    }
    return 0;
}

/** @brief This function is called whenever the device is being written to from user space i.e.
 *  data is sent to the device from the user. The data is copied to the message[] array in this
 *  LKM using the sprintf() function along with the length of the string.
 *  @param filep A pointer to a file object
 *  @param buffer The buffer to that contains the string to write to the device
 *  @param len The length of the array of data that is being passed in the const char buffer
 *  @param offset The offset if required
 */
static ssize_t ssd1306_write(struct file *filep, const char *buffer, size_t len, loff_t *offset){
    int ret;
    ret = copy_from_user( message , buffer , len);   // appending received string with its length
    // size_of_message = strlen(message);                 // store the length of the stored message
    // printk(KERN_INFO "ssd1306: Received %s : %zu characters from the user\n", message , len);
    sentStringSSD1306( message , len );
    // msleep(1000);
    // printk(KERN_INFO "ssd1306: WRITE\n");
    return len;
}

/** @brief The device release function that is called whenever the device is closed/released by
 *  the userspace program
 *  @param inodep A pointer to an inode object (defined in linux/fs.h)
 *  @param filep A pointer to a file object (defined in linux/fs.h)
 */
static int ssd1306_release(struct inode *inodep, struct file *filep){
//    printk(KERN_INFO "ssd1306: Device successfully closed\n");
//    sentImgSSD1306( tuxV );
   return 0;
}

static long ssd1306_ioctl(struct file *file, unsigned int cmd, unsigned long args)
{
    // pr_info("cmd: %x\n", cmd);
    // pr_info("arg: %ld\n", args);

    if( _IOC_TYPE(cmd) != _SSD1306_IOC_MAGIC_ ) {
        return -EINVAL;
    }

    if( _IOC_NR(cmd) > _SSD1306_IOC_CMD_MAX_ ) {
        return -EINVAL;
    }

	switch( cmd )
    {
		case _SSD1306_IOC_CLEAR_:
			clearDisplaySSD1306();
        case _SSD1306_IOC_HOME_:
            homeDisplaySSD1306();
		break;

		case _SSD1306_IOC_NORMAL_:
            sentCommandSSD1306( _SSD1306_NORMALDISPLAY_ );
		break;

		case _SSD1306_IOC_INVERT_:
            sentCommandSSD1306( _SSD1306_INVERTDISPLAY_ );
		break;

		case _SSD1306_IOC_CLR_PAGE_:
            clearPageSSD1306( (uint8_t)args );
		break;

        case _SSD1306_IOC_SET_PAGE_:
            setPageSSD1306( (uint8_t)args );
		break;

		default:
			return -EINVAL;
	}

	return 0;
}

static const struct i2c_device_id ssd1306_i2c_id[] = {
    { "ssd1306", 0 },
    { }
};

MODULE_DEVICE_TABLE(i2c, ssd1306_i2c_id);

static const struct of_device_id ssd1306_of_match[] = {
    { .compatible = "trec,ssd1306" },
    { }
};

MODULE_DEVICE_TABLE(of, ssd1306_of_match);

static int ssd1306_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
    char initSec[] = {0x00, 0xAE, 0xD5, 0x80, 0xA8, 0x3F, 0xD3, 0x00, 0x40, 0x8D, 0x14, 0x20, 0x00, 0xA1, 0xC8, 0xDA, 0x12, 0x81, 0xCF, 0xD9, 0xF1, 0xDB, 0x40, 0xA4, 0xA6, 0x2E, 0xAF};

    pr_info("ssd1306_probe!\n");

    ssd1306_i2c = client;

    i2c_master_send( ssd1306_i2c , initSec , sizeof(initSec) );

    clearDisplaySSD1306();

	sentImgSSD1306( tuxV );
    sentCommandSSD1306( _SSD1306_INVERTDISPLAY_);

    printk(KERN_INFO "ssd1306: Initializing the ssd1306 LKM\n");

    // Try to dynamically allocate a major number for the device -- more difficult but worth it
    majorNumber = register_chrdev(0, DEVICE_NAME, &fops);
    if (majorNumber<0){
        printk(KERN_ALERT "ssd1306 failed to register a major number\n");
        return majorNumber;
    }
    printk(KERN_INFO "ssd1306: registered correctly with major number %d\n", majorNumber);

    // Register the device class
    ssd1306Class = class_create(THIS_MODULE, CLASS_NAME);
    if (IS_ERR(ssd1306Class)){                // Check for error and clean up if there is
        unregister_chrdev(majorNumber, DEVICE_NAME);
        printk(KERN_ALERT "Failed to register device class\n");
        return PTR_ERR(ssd1306Class);          // Correct way to return an error on a pointer
    }
    printk(KERN_INFO "ssd1306: device class registered correctly\n");

    // Register the device driver
    ssd1306Device = device_create(ssd1306Class, NULL, MKDEV(majorNumber, 0), NULL, DEVICE_NAME);
    if (IS_ERR(ssd1306Device)){               // Clean up if there is an error
        class_destroy(ssd1306Class);           // Repeated code but the alternative is goto statements
        unregister_chrdev(majorNumber, DEVICE_NAME);
        printk(KERN_ALERT "Failed to create the device\n");
        return PTR_ERR(ssd1306Device);
    }
    printk(KERN_INFO "ssd1306: device class created correctly\n"); // Made it! device was initialized

    return 0;
}

static int ssd1306_remove(struct i2c_client *client)
{
    pr_info("ssd1306_remove!\n");
    //clearDisplaySSD1306(client);
    sentCommandSSD1306( _SSD1306_DISPLAYOFF_ );

    device_destroy(ssd1306Class, MKDEV(majorNumber, 0));     // remove the device
    class_unregister(ssd1306Class);                          // unregister the device class
    class_destroy(ssd1306Class);                             // remove the device class
    unregister_chrdev(majorNumber, DEVICE_NAME);             // unregister the major number
    printk(KERN_INFO "ssd1306: Goodbye from the LKM!\n");

    return 0;
}

static struct i2c_driver ssd1306_i2c_driver = {
    .driver = {
        .name = "ssd1306",
        .of_match_table = ssd1306_of_match,
    },
    .probe = ssd1306_probe,
    .remove = ssd1306_remove,
    .id_table = ssd1306_i2c_id
};

module_i2c_driver(ssd1306_i2c_driver);

/**********************************************************************/
/* Modules licensing/description block.                               */
/**********************************************************************/
MODULE_LICENSE("GPL");
MODULE_AUTHOR("@trecetp - Leonardo Urrego Laiton");
MODULE_DESCRIPTION("MSE4Co.19IMD Kernel Module SSD1306 OLED I2C");
MODULE_VERSION("0.1");            ///< A version number to inform users
