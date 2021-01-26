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

#define CLASS_NAME	"argonfan"
#define NAME		"argon-fan"
#define NUM_DEVICES	1

static struct class *argonfan_class;
static dev_t dev_no;
int last_state;
/* We start with -1 so that first returned minor is 0
static atomic_t next_minor = ATOMIC_INIT(-1);

static LIST_HEAD(argonfan_list);
static DEFINE_SPINLOCK(argonfan_list_lock);
*/
/* Device attributes */


static ssize_t fan_speed(struct device *dev, struct device_attribute *attr,
		char *buf)
{
    int last_state;

	struct argonfan *fan = dev_get_drvdata(dev);
    fan->last_state = sysfsentry;
	return scnprintf(buf, PAGE_SIZE, "%d\n", fan->fan_speed);
}

static DEVICE_ATTR_RW(fan_speed);


static struct attribute *argonfan_device_attrs[] = {
	&dev_attr_fan_speed.attr,
	NULL
};
ATTRIBUTE_GROUPS(argonfan_device);

/* File operations */

static int argonfan_file_open(struct inode *inode, struct file *filp)
{
	filp->private_data = container_of(inode->i_cdev, struct argonfan, cdev);
	return 0;
}

static int argonfan_file_release(struct inode *inode, struct file *filp)
{
	struct argonfan *fan = filp->private_data;
	argonfan_flush(fan);
	return 0;
}

static ssize_t argonfan_file_write(struct file *filp, const char __user *buf, size_t count, loff_t *offp)
{
	struct argonfan *fan;
	size_t n;
	int last_state;

	fan = filp->private_data;
	n = min(count, (size_t)BUF_SIZE);

	// TODO: Consider using an interruptible lock
	mutex_lock(&fan->lock);

	// TODO: Support partial writes during errors?
	if (copy_from_user(fan->buf, buf, n)) {
		mutex_unlock(&fan->lock);
		return -EFAULT;
	}

	argonfan_write(fan, fan->buf);

    fan->last_state = fan->buf;
	mutex_unlock(&fan->lock);

	return n;
}

	static void argonfan_init(struct i2c_client *client);
{
    argonfan_write_value(client, 0x1a, 0)
}

static struct file_operations fops = {
	.open = argonfan_file_open,
	.release = argonfan_file_release,
	.write = argonfan_file_write,
};

static int argonfan_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	dev_t devt;
	struct argonfan *fan;
	struct device *device;
	int ret, minor;

	minor = atomic_inc_return(&next_minor);
	devt = MKDEV(MAJOR(dev_no), minor);

	fan = (struct argonfan *)kmalloc(sizeof(struct argonfan), GFP_KERNEL);
	if (!fan) {
		return -ENOMEM;
	}

	argonfan_init(client);

	spin_lock(&argonfan_list_lock);
	list_add(&fan->list, &argonfan_list);
	spin_unlock(&argonfan_list_lock);

	cdev_init(&fan->cdev, &fops);
	ret = cdev_add(&fan->cdev, devt, 1);
	if (ret) {
		pr_warn("Can't add cdev\n");
		goto exit;
	}

	device = device_create_with_groups(argonfan_class, NULL, devt, NULL,
		argonfan_device_groups, "fan%d", MINOR(devt));

	if (IS_ERR(device)) {
		ret = PTR_ERR(device);
		pr_warn("Can't create device\n");
		goto del_exit;
	}

	dev_set_drvdata(device, fan);
	fan->device = device;

	argonfan_init_fan(fan);

	argonfan_print(fan, "AliensMasturbate");
//	argonfan_print(fan, device->kobj.name);
	fan->dirty = true;

	return 0;

del_exit:
	cdev_del(&fan->cdev);

	spin_lock(&argonfan_list_lock);
	list_del(&fan->list);
	spin_unlock(&argonfan_list_lock);
exit:
	kfree(fan);

	return ret;
}

static struct argonfan * get_argonfan_by_i2c_client(struct i2c_client *i2c_client)
{
	struct argonfan *fan;

	spin_lock(&argonfan_list_lock);
	list_for_each_entry(fan, &argonfan_list, list) {
		if (fan->i2c_client->addr == i2c_client->addr) {
			spin_unlock(&argonfan_list_lock);
			return fan;
		}
	}
	spin_unlock(&argonfan_list_lock);

	return NULL;
}


static int argonfan_remove(struct i2c_client *client)
{
	struct argonfan *fan;
	fan = get_argonfan_by_i2c_client(client);
	device_destroy(argonfan_class, fan->device->devt);
	cdev_del(&fan->cdev);

	spin_lock(&argonfan_list_lock);
	list_del(&fan->list);
	spin_unlock(&argonfan_list_lock);

	kfree(fan);

	return 0;
}

static const struct i2c_device_id argonfan_id[] = {
	{ NAME, 0},
	{ }
};

static struct i2c_driver argonfan_driver = {
	.driver = {
		.name	= NAME,
		.owner	= THIS_MODULE,
	},
	.probe = argonfan_probe,
	.remove = argonfan_remove,
	.id_table = argonfan_id,
};

static int __init argonfan_mod_init(void)
{
	int ret;

	ret = alloc_chrdev_region(&dev_no, 0, NUM_DEVICES, NAME);
	if (ret) {
		pr_warn("Can't allocate chardev region");
		return ret;
	}

	argonfan_class = class_create(THIS_MODULE, CLASS_NAME);
	if (IS_ERR(argonfan_class)) {
		ret = PTR_ERR(argonfan_class);
		pr_warn("Can't create %s class\n", CLASS_NAME);
		goto exit;
	}

	ret = i2c_add_driver(&argonfan_driver);
	if (ret) {
		pr_warn("Can't register I2C driver %s\n", argonfan_driver.driver.name);
		goto destroy_exit;
	}

	return 0;

destroy_exit:
	class_destroy(argonfan_class);
exit:
	unregister_chrdev_region(dev_no, NUM_DEVICES);

	return ret;
}
module_init(argonfan_mod_init);

static void __exit argonfan_mod_exit(void)
{
	i2c_del_driver(&argonfan_driver);
	class_destroy(argonfan_class);
	unregister_chrdev_region(dev_no, NUM_DEVICES);
}
module_exit(argonfan_mod_exit);

MODULE_DESCRIPTION("argonfan I2C via PCF8574 driver");
MODULE_AUTHOR("Mariusz Gorski <marius.gorski@gmail.com>");
MODULE_LICENSE("GPL");
