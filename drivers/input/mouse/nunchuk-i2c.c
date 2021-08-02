#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/workqueue.h>
#include <linux/input.h>
#include <linux/i2c.h>

#define NUNCHUK_I2C_REPORT_SIZE 6

struct nunchuk_report {
	u8	joy_x;
	u8	joy_y;
	u16	acc_x;
	u16	acc_y;
	u16	acc_z;
	u8	C;
	u8	Z;
};

struct nunchuk_device {
	struct i2c_client 	*client;
	struct input_dev	*input;
	struct workqueue_struct	*wq;
	struct delayed_work	dwork;
	int			refn;
	u8			report_buf[NUNCHUK_I2C_REPORT_SIZE];
	struct nunchuk_report	report;
};

static atomic_t refcount = ATOMIC_INIT(0);

static inline struct nunchuk_device *to_nunchuk_device(struct work_struct *work)
{
	return container_of(to_delayed_work(work), struct nunchuk_device, dwork);
}

static void i2c_smbus_read_byte_array(struct i2c_client *client, u8 length, u8 *values)
{
	u8 i;
	for (i = 0; i < length; i++) {
		values[i] = i2c_smbus_read_byte(client);
	}
}

static void nunchuk_init_reporting(struct nunchuk_device *nunchuk)
{
	i2c_smbus_write_byte_data(nunchuk->client, 0xF0, 0x55);
	i2c_smbus_write_byte_data(nunchuk->client, 0xFB, 0x00);
	/* Prepare the next reading */
	i2c_smbus_write_byte(nunchuk->client, 0x00);
}

static void nunchuk_correct_report(struct nunchuk_device *nunchuk)
{
	struct nunchuk_report *report = &nunchuk->report;
	u8 *report_buf = nunchuk->report_buf;

	report->joy_x = report_buf[0];
	report->joy_y = report_buf[1];
	report->acc_x = (((report_buf[5]>>2) & 0b11) | ((u16)report_buf[2])<<2);
	report->acc_y = (((report_buf[5]>>4) & 0b11) | ((u16)report_buf[3])<<2);
	report->acc_z = (((report_buf[5]>>6) & 0b11) | ((u16)report_buf[4])<<2);
	report->Z = (~report_buf[5]) & 0b1;
	report->C = ((~report_buf[5])>>1) & 0b1;
}

static void workqueue_function(struct work_struct *work)
{
	struct nunchuk_device *nunchuk;
	nunchuk = to_nunchuk_device(work);

	i2c_smbus_read_byte_array(nunchuk->client,
		NUNCHUK_I2C_REPORT_SIZE, nunchuk->report_buf);

	nunchuk_correct_report(nunchuk);

	input_report_rel(nunchuk->input, REL_X, (+nunchuk->report.joy_x - 128)/10);
	input_report_rel(nunchuk->input, REL_Y, (-nunchuk->report.joy_y + 128)/10);
	input_report_rel(nunchuk->input, REL_RX, nunchuk->report.acc_x);
	input_report_rel(nunchuk->input, REL_RY, nunchuk->report.acc_y);
	input_report_rel(nunchuk->input, REL_RZ, nunchuk->report.acc_z);
	input_report_key(nunchuk->input, BTN_LEFT, nunchuk->report.Z);
	input_report_key(nunchuk->input, BTN_RIGHT, nunchuk->report.C);
	input_sync(nunchuk->input);

	/* Prepare the next reading */
	i2c_smbus_write_byte(nunchuk->client, 0x00);

	queue_delayed_work(nunchuk->wq, &nunchuk->dwork, msecs_to_jiffies(10));
}

static int nunchuk_i2c_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	struct nunchuk_device *nunchuk;
	int err;

	if (!i2c_check_functionality(client->adapter,
			I2C_FUNC_SMBUS_BYTE |
			I2C_FUNC_SMBUS_WRITE_BYTE_DATA)) {
		printk(KERN_ERR "nunchuk_i2c_probe: "
			"unsupported adapter\n");
		return -EIO;
	}
	else{
		printk(KERN_ALERT "nunchuk_i2c : nunchuk found.\n");
	}

	nunchuk = kzalloc(sizeof(*nunchuk), GFP_KERNEL);
	if (nunchuk == NULL) {
		return -ENOMEM;
	}

	nunchuk->client = client;
	nunchuk->input = input_allocate_device();
	if (nunchuk->input == NULL) {
		printk(KERN_ERR "nunchuk_i2c_probe: "
			"not enough memory\n");
		err = -ENODEV;
		goto err_freenun;
	}

	nunchuk->refn = atomic_inc_return(&refcount) - 1;
	nunchuk->input->name = "nunchuk";

	set_bit(EV_REL, nunchuk->input->evbit);
	set_bit(REL_X, nunchuk->input->relbit);
	set_bit(REL_Y, nunchuk->input->relbit);
	set_bit(REL_RX, nunchuk->input->relbit);
	set_bit(REL_RX, nunchuk->input->relbit);
	set_bit(REL_RY, nunchuk->input->relbit);

	set_bit(EV_KEY, nunchuk->input->evbit);
	set_bit(BTN_LEFT, nunchuk->input->keybit);
	set_bit(BTN_RIGHT, nunchuk->input->keybit);

	err = input_register_device(nunchuk->input);
	if (err) {
		printk(KERN_ERR "nunchuk_i2c_probe: "
			"failed to register input device (%d)\n", err);
		goto err_freedev;
	}

	nunchuk_init_reporting(nunchuk);

	nunchuk->wq = create_singlethread_workqueue("nunchuk");
	INIT_DELAYED_WORK(&nunchuk->dwork, workqueue_function);

	i2c_set_clientdata(client, nunchuk);

	queue_delayed_work(nunchuk->wq, &nunchuk->dwork, msecs_to_jiffies(50));

	return 0;

err_freedev:
	input_free_device(nunchuk->input);
err_freenun:
	kfree(nunchuk);
	return err;
}

static int nunchuk_i2c_remove(struct i2c_client *client)
{
	struct nunchuk_device *nunchuk;

	nunchuk = i2c_get_clientdata(client);

	cancel_delayed_work(&nunchuk->dwork);
	flush_workqueue(nunchuk->wq);
	destroy_workqueue(nunchuk->wq);

	input_unregister_device(nunchuk->input);

	kfree(nunchuk);

	return 0;
}


static const struct i2c_device_id nunchuk_i2c_idtable[] = {
	{"nunchuk-i2c", 0},
	{ }
};

MODULE_DEVICE_TABLE(i2c, nunchuk_i2c_idtable);

static struct i2c_driver nunchuk_i2c_driver = {
	.driver		= {
		.owner	= THIS_MODULE,
		.name	= "nunchuk-i2c",
	},
	.id_table	= nunchuk_i2c_idtable,
	.probe		= nunchuk_i2c_probe,
	.remove		= nunchuk_i2c_remove,
};

static int __init nunchuk_i2c_init(void)
{
	int err;

	err = i2c_add_driver(&nunchuk_i2c_driver);
	if (err) {
		printk(KERN_ERR "nunchuk_i2c_init: "
			"failed to add I2C driver (%d)\n", err);
		return err;
	}
	printk(KERN_ALERT "nunchuk_i2c : Init ok.\n");	

	return 0;
}

static void __exit nunchuk_i2c_exit(void)
{
	i2c_del_driver(&nunchuk_i2c_driver);
}

module_init(nunchuk_i2c_init);
module_exit(nunchuk_i2c_exit);

MODULE_AUTHOR("Sergi Granell");
MODULE_AUTHOR("Andrea Campanella");
MODULE_DESCRIPTION("Nunchuk I2C input driver");
MODULE_LICENSE("GPL");
