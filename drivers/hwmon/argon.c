#include <linux/module.h>
#include <linux/fs.h>
#include <linux/printk.h>
#include <linux/device.h>
#include <linux/i2c.h>
#include <linux/delay.h>
#include <linux/hwmon.h>
#include <linux/hwmon-sysfs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/list.h>
#include <linux/sysfs.h>
#include <linux/slab.h>
#include <linux/err.h>
#include <linux/mutex.h>

#define CLASS_NAME	"argonfan"
#define NAME		"argon-fan"
#define ARGONFAN_CTL      0x00

static const unsigned short normal_i2c[] = { 0x1a, I2C_CLIENT_END };



static struct i2c_device_id argonfan_idtable[] = {
      { "argonfan", 0 },
      { }
};
MODULE_DEVICE_TABLE(i2c, argonfan_idtable);

struct argonfan_data {
	struct i2c_client *client;
	struct mutex update_lock;
	u8 fan1_speed;
//	u8 fan1_min;
//	u8 fan1_max;
	u8 fan1_input;
	u8 fan1_target;
    u8 fan1_label;
};


int argonfan_write_value(struct i2c_client *client, u8 reg, u8 value)
{
//      printk(KERN_INFO "setting fan to %d\n", value);
      return i2c_smbus_write_byte_data(client, ARGONFAN_CTL, value);
}

static ssize_t fan1_speed_show(struct device *dev, struct device_attribute *attr,
		char *buf)
{
	struct argonfan_data *data = dev_get_drvdata(dev);

    int ret2;
    ret2 = data->fan1_speed;

	return scnprintf(buf, PAGE_SIZE, "%d\n", ret2);
}

static ssize_t fan1_speed_store(struct device *dev, struct device_attribute *attr,
			    const char *buf, size_t count)
{
	struct argonfan_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	u8 value;
	u8 ret2;
	ret2 = kstrtou8(buf, 10, &value);
    data->fan1_speed = value;

	mutex_lock(&data->update_lock);

//    printk(KERN_INFO "setting fan to %d\n", value);
    argonfan_write_value(client, ARGONFAN_CTL, value);

	mutex_unlock(&data->update_lock);
	return count;
}


static ssize_t fan1_input_show(struct device *dev, struct device_attribute *attr,
		char *buf)
{
	struct argonfan_data *data = dev_get_drvdata(dev);

    int ret2;
    ret2 = data->fan1_speed;

	return scnprintf(buf, PAGE_SIZE, "%d\n", ret2);
}

static ssize_t fan1_target_show(struct device *dev, struct device_attribute *attr,
		char *buf)
{
	struct argonfan_data *data = dev_get_drvdata(dev);

    int ret2;
    ret2 = data->fan1_speed;

	return scnprintf(buf, PAGE_SIZE, "%d\n", ret2);
}

static ssize_t fan1_target_store(struct device *dev, struct device_attribute *attr,
			    const char *buf, size_t count)
{
	struct argonfan_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	u8 value;
	u8 ret2;
	ret2 = kstrtou8(buf, 10, &value);
    data->fan1_speed = value;

	mutex_lock(&data->update_lock);

//    printk(KERN_INFO "setting fan to %d\n", value);
    argonfan_write_value(client, ARGONFAN_CTL, value);

	mutex_unlock(&data->update_lock);
	return count;
}

static ssize_t fan1_label_show(struct device *dev, struct device_attribute *attr,
		char *buf)
{

	return scnprintf(buf, PAGE_SIZE, "argonefan\n");
}

static DEVICE_ATTR_RW(fan1_speed);
static DEVICE_ATTR_RO(fan1_input);
static DEVICE_ATTR_RW(fan1_target);
static DEVICE_ATTR_RO(fan1_label);

static struct attribute *argonfan_attrs[] = {
	&dev_attr_fan1_speed.attr,
	&dev_attr_fan1_input.attr,
	&dev_attr_fan1_target.attr,
	&dev_attr_fan1_label.attr,
    NULL
};

ATTRIBUTE_GROUPS(argonfan);

static int argonfan_remove(struct i2c_client *client)
{

	struct argonfan_data *data = i2c_get_clientdata(client);
	mutex_lock(&data->update_lock);

    argonfan_write_value(client, ARGONFAN_CTL, 0);

	mutex_unlock(&data->update_lock);
	return 0;
}



static int argonfan_probe(struct i2c_client *client,
                     const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct argonfan_data *data;
	struct device *hwmon_dev;
	data = devm_kzalloc(dev, sizeof(struct argonfan_data), GFP_KERNEL);

	i2c_set_clientdata(client, data);
	data->client = client;

	hwmon_dev = devm_hwmon_device_register_with_groups(dev, client->name,
							   data,
							   argonfan_groups);
    mutex_lock(&data->update_lock);

    argonfan_write_value(client, ARGONFAN_CTL, 0);
//    i2c_smbus_write_byte_data(client, ARGONFAN_CTL, value);

	mutex_unlock(&data->update_lock);
	return PTR_ERR_OR_ZERO(hwmon_dev);
    return 0;
}

static const struct of_device_id argonfan_of_match[] = {
	{ .compatible = "argon,argonfan" },
	{}
};
MODULE_DEVICE_TABLE(of, argonfan_of_match);

static struct i2c_driver argonfan_driver = {
	  .class		= I2C_CLASS_HWMON,
      .driver = {
              .name   = "argonfan",
      },

      .id_table       = argonfan_idtable,
      .address_list   = normal_i2c,
      .probe           = argonfan_probe,

      .remove       = argonfan_remove, /* optional */

};


module_i2c_driver(argonfan_driver);


MODULE_AUTHOR("Ben Maddocks bm16ton@gmail");
MODULE_DESCRIPTION("Driver for ArgonFan PiHat");
MODULE_LICENSE("GPL");
