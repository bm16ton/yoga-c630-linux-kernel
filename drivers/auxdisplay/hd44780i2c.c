#include <linux/module.h>
#include <linux/fs.h>
#include <linux/printk.h>
#include <linux/device.h>
#include <linux/i2c.h>
#include <linux/delay.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/list.h>

#include "hd44780i2c.h"

#define CLASS_NAME	"hd44780i2c"
#define NAME		"hd44780-i2c"
#define NUM_DEVICES	8

static struct class *hd44780i2c_class;
static dev_t dev_no;
/* We start with -1 so that first returned minor is 0 */
static atomic_t next_minor = ATOMIC_INIT(-1);

static LIST_HEAD(hd44780i2c_list);
static DEFINE_SPINLOCK(hd44780i2c_list_lock);

/* Device attributes */

static ssize_t geometry_show(struct device *dev, struct device_attribute *attr,
		char *buf)
{
	struct hd44780i2c *lcd;
	struct hd44780i2c_geometry *geo;

	lcd = dev_get_drvdata(dev);
	geo = lcd->geometry;

	return scnprintf(buf, PAGE_SIZE, "%dx%d\n", geo->cols, geo->rows);
}

static ssize_t geometry_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	struct hd44780i2c *lcd;
	struct hd44780i2c_geometry *geo;
	int cols = 0, rows = 0, i;

	sscanf(buf, "%dx%d", &cols, &rows);

	for (i = 0; hd44780i2c_geometries[i] != NULL; i++) {
		geo = hd44780i2c_geometries[i];

		if (geo->cols == cols && geo->rows == rows) {
			lcd = dev_get_drvdata(dev);

			mutex_lock(&lcd->lock);
			hd44780i2c_set_geometry(lcd, geo);
			mutex_unlock(&lcd->lock);

			break;
		}
	}

	return count;
}
static DEVICE_ATTR_RW(geometry);

static ssize_t backlight_show(struct device *dev, struct device_attribute *attr,
		char *buf)
{
	struct hd44780i2c *lcd = dev_get_drvdata(dev);

	return scnprintf(buf, PAGE_SIZE, "%d\n", lcd->backlight);
}

static ssize_t backlight_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	struct hd44780i2c *lcd = dev_get_drvdata(dev);

	mutex_lock(&lcd->lock);
	hd44780i2c_set_backlight(lcd, buf[0] == '1');
	mutex_unlock(&lcd->lock);

	return count;
}
static DEVICE_ATTR_RW(backlight);

static ssize_t cursor_blink_show(struct device *dev, struct device_attribute *attr,
		char *buf)
{
	struct hd44780i2c *lcd = dev_get_drvdata(dev);

	return scnprintf(buf, PAGE_SIZE, "%d\n", lcd->cursor_blink);
}

static ssize_t cursor_blink_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	struct hd44780i2c *lcd = dev_get_drvdata(dev);

	mutex_lock(&lcd->lock);
	hd44780i2c_set_cursor_blink(lcd, buf[0] == '1');
	mutex_unlock(&lcd->lock);

	return count;
}
static DEVICE_ATTR_RW(cursor_blink);

static ssize_t cursor_display_show(struct device *dev, struct device_attribute *attr,
		char *buf)
{
	struct hd44780i2c *lcd = dev_get_drvdata(dev);

	return scnprintf(buf, PAGE_SIZE, "%d\n", lcd->cursor_display);
}

static ssize_t cursor_display_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	struct hd44780i2c *lcd = dev_get_drvdata(dev);

	mutex_lock(&lcd->lock);
	hd44780i2c_set_cursor_display(lcd, buf[0] == '1');
	mutex_unlock(&lcd->lock);

	return count;
}
static DEVICE_ATTR_RW(cursor_display);

static struct attribute *hd44780i2c_device_attrs[] = {
	&dev_attr_geometry.attr,
	&dev_attr_backlight.attr,
	&dev_attr_cursor_blink.attr,
	&dev_attr_cursor_display.attr,
	NULL
};
ATTRIBUTE_GROUPS(hd44780i2c_device);

/* File operations */

static int hd44780i2c_file_open(struct inode *inode, struct file *filp)
{
	filp->private_data = container_of(inode->i_cdev, struct hd44780i2c, cdev);
	return 0;
}

static int hd44780i2c_file_release(struct inode *inode, struct file *filp)
{
	struct hd44780i2c *lcd = filp->private_data;
	hd44780i2c_flush(lcd);
	return 0;
}

static ssize_t hd44780i2c_file_write(struct file *filp, const char __user *buf, size_t count, loff_t *offp)
{
	struct hd44780i2c *lcd;
	size_t n;

	lcd = filp->private_data;
	n = min(count, (size_t)BUF_SIZE);

	// TODO: Consider using an interruptible lock
	mutex_lock(&lcd->lock);

	// TODO: Support partial writes during errors?
	if (copy_from_user(lcd->buf, buf, n)) {
		mutex_unlock(&lcd->lock);
		return -EFAULT;
	}

	hd44780i2c_write(lcd, lcd->buf, n);

	mutex_unlock(&lcd->lock);

	return n;
}

static void hd44780i2c_init(struct hd44780i2c *lcd, struct hd44780i2c_geometry *geometry,
		struct i2c_client *i2c_client)
{
	lcd->geometry = geometry;
	lcd->i2c_client = i2c_client;
	lcd->pos.row = 0;
	lcd->pos.col = 0;
	memset(lcd->esc_seq_buf.buf, 0, ESC_SEQ_BUF_SIZE);
	lcd->esc_seq_buf.length = 0;
	lcd->is_in_esc_seq = false;
	lcd->backlight = true;
	lcd->cursor_blink = true;
	lcd->cursor_display = true;
	mutex_init(&lcd->lock);
}

static struct file_operations fops = {
	.open = hd44780i2c_file_open,
	.release = hd44780i2c_file_release,
	.write = hd44780i2c_file_write,
};

static int hd44780i2c_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	dev_t devt;
	struct hd44780i2c *lcd;
	struct device *device;
	int ret, minor;

	minor = atomic_inc_return(&next_minor);
	devt = MKDEV(MAJOR(dev_no), minor);

	lcd = (struct hd44780i2c *)kmalloc(sizeof(struct hd44780i2c), GFP_KERNEL);
	if (!lcd) {
		return -ENOMEM;
	}

	hd44780i2c_init(lcd, hd44780i2c_geometries[0], client);

	spin_lock(&hd44780i2c_list_lock);
	list_add(&lcd->list, &hd44780i2c_list);
	spin_unlock(&hd44780i2c_list_lock);

	cdev_init(&lcd->cdev, &fops);
	ret = cdev_add(&lcd->cdev, devt, 1);
	if (ret) {
		pr_warn("Can't add cdev\n");
		goto exit;
	}

	device = device_create_with_groups(hd44780i2c_class, NULL, devt, NULL,
		hd44780i2c_device_groups, "lcd%d", MINOR(devt));

	if (IS_ERR(device)) {
		ret = PTR_ERR(device);
		pr_warn("Can't create device\n");
		goto del_exit;
	}

	dev_set_drvdata(device, lcd);
	lcd->device = device;

	hd44780i2c_init_lcd(lcd);

	hd44780i2c_print(lcd, "AliensMasturbate");
//	hd44780i2c_print(lcd, device->kobj.name);
	lcd->dirty = true;

	return 0;

del_exit:
	cdev_del(&lcd->cdev);

	spin_lock(&hd44780i2c_list_lock);
	list_del(&lcd->list);
	spin_unlock(&hd44780i2c_list_lock);
exit:
	kfree(lcd);

	return ret;
}

static struct hd44780i2c * get_hd44780i2c_by_i2c_client(struct i2c_client *i2c_client)
{
	struct hd44780i2c *lcd;

	spin_lock(&hd44780i2c_list_lock);
	list_for_each_entry(lcd, &hd44780i2c_list, list) {
		if (lcd->i2c_client->addr == i2c_client->addr) {
			spin_unlock(&hd44780i2c_list_lock);
			return lcd;
		}
	}
	spin_unlock(&hd44780i2c_list_lock);

	return NULL;
}


static int hd44780i2c_remove(struct i2c_client *client)
{
	struct hd44780i2c *lcd;
	lcd = get_hd44780i2c_by_i2c_client(client);
	device_destroy(hd44780i2c_class, lcd->device->devt);
	cdev_del(&lcd->cdev);

	spin_lock(&hd44780i2c_list_lock);
	list_del(&lcd->list);
	spin_unlock(&hd44780i2c_list_lock);

	kfree(lcd);

	return 0;
}

static const struct i2c_device_id hd44780i2c_id[] = {
	{ NAME, 0},
	{ }
};

static struct i2c_driver hd44780i2c_driver = {
	.driver = {
		.name	= NAME,
		.owner	= THIS_MODULE,
	},
	.probe = hd44780i2c_probe,
	.remove = hd44780i2c_remove,
	.id_table = hd44780i2c_id,
};

static int __init hd44780i2c_mod_init(void)
{
	int ret;

	ret = alloc_chrdev_region(&dev_no, 0, NUM_DEVICES, NAME);
	if (ret) {
		pr_warn("Can't allocate chardev region");
		return ret;
	}

	hd44780i2c_class = class_create(THIS_MODULE, CLASS_NAME);
	if (IS_ERR(hd44780i2c_class)) {
		ret = PTR_ERR(hd44780i2c_class);
		pr_warn("Can't create %s class\n", CLASS_NAME);
		goto exit;
	}

	ret = i2c_add_driver(&hd44780i2c_driver);
	if (ret) {
		pr_warn("Can't register I2C driver %s\n", hd44780i2c_driver.driver.name);
		goto destroy_exit;
	}

	return 0;

destroy_exit:
	class_destroy(hd44780i2c_class);
exit:
	unregister_chrdev_region(dev_no, NUM_DEVICES);

	return ret;
}
module_init(hd44780i2c_mod_init);

static void __exit hd44780i2c_mod_exit(void)
{
	i2c_del_driver(&hd44780i2c_driver);
	class_destroy(hd44780i2c_class);
	unregister_chrdev_region(dev_no, NUM_DEVICES);
}
module_exit(hd44780i2c_mod_exit);

MODULE_DESCRIPTION("HD44780I2C I2C via PCF8574 driver");
MODULE_AUTHOR("Mariusz Gorski <marius.gorski@gmail.com>");
MODULE_LICENSE("GPL");
