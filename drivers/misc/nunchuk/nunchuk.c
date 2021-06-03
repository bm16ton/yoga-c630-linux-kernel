#include <linux/delay.h>
#include <linux/device.h>
#include <linux/i2c.h>
#include <linux/input.h>
//#include <linux/input-polldev.h>
#include <linux/init.h>
#include <linux/module.h>

#define NUNCHUK_POLL_INTERVAL (50)

struct nunchuk_dev {
	struct i2c_client *i2c_client;
	struct input_polled_dev *polled_input;
};

static u8 zpressed;
static u8 cpressed;

static s32 nunchuk_read_registers(struct i2c_client *client, u8 *buf, int buf_size) {
	s32 status;

	mdelay(10);

	buf[0] = 0x00;
	status = i2c_master_send(client, buf, 1);
	if (status < 0) {
		return status;
	}

	mdelay(10);

	return i2c_master_recv(client, buf, buf_size);
}

static void nunchuk_poll(struct input_polled_dev *polled_input) {
	u8 buf[6];
	u8 joystick_x;
	u8 joystick_y;
	u16 accel_x;
	u16 accel_y;
	u16 accel_z;
	struct i2c_client *client;
	struct nunchuk_dev *nunchuk;
	s32 status;

	nunchuk = polled_input->private;
	client = nunchuk->i2c_client;

	status = nunchuk_read_registers(client, buf, ARRAY_SIZE(buf));
	if (status < 0) {
		dev_err(&client->dev, "Error reading nunchuk registers: %0x", status);
		return;
	}

	/* See http://web.engr.oregonstate.edu/~johnstay/ece375/pdf/nunchuk.pdf */
	joystick_x = buf[0];
	joystick_y = buf[1];
	accel_x = (buf[2] << 2) | ((buf[5] >> 2) & 0x3);
	accel_y = (buf[3] << 2) | ((buf[5] >> 4) & 0x3);
	accel_z = (buf[4] << 2) | ((buf[5] >> 6) & 0x3);
	zpressed = !(buf[5] & 0x1);
	cpressed = !(buf[5] & 0x2);

	input_report_abs(polled_input->input, ABS_X, joystick_x);
	input_report_abs(polled_input->input, ABS_Y, joystick_y);
	input_report_abs(polled_input->input, ABS_RX, accel_x);
	input_report_abs(polled_input->input, ABS_RY, accel_y);
	input_report_abs(polled_input->input, ABS_RZ, accel_z);

	input_event(polled_input->input, EV_KEY, BTN_Z, zpressed);
	input_event(polled_input->input, EV_KEY, BTN_C, cpressed);


	input_sync(polled_input->input);
}

static int nunchuk_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	u8 buf[2];
	struct input_dev *input;
	struct nunchuk_dev *nunchuk;
	s32 status;
	struct input_polled_dev *polled_input;

	/* Get everything ready */
	nunchuk = devm_kzalloc(&client->dev, sizeof(*nunchuk), GFP_KERNEL);
	if (nunchuk == NULL) {
		status = -ENOMEM;
		goto exit;
	}

	polled_input = input_allocate_device();
	if (polled_input == NULL) {
		status = -ENOMEM;
		goto exit_nunchuk_dev;
	}

	nunchuk->i2c_client = client;
	nunchuk->polled_input = polled_input;
	polled_input->private = nunchuk;
	i2c_set_clientdata(client, nunchuk);
	input = polled_input->input;
	input->dev.parent = &client->dev;

	input->name = "Wii Nunchuk";
	input->id.bustype = BUS_I2C;
	set_bit(EV_KEY, input->evbit);
	set_bit(EV_ABS, input->evbit);
	set_bit(ABS_X, input->absbit);
	set_bit(ABS_Y, input->absbit);
	set_bit(ABS_Z, input->absbit);
	set_bit(ABS_RX, input->absbit);
	set_bit(ABS_RY, input->absbit);
	set_bit(ABS_RZ, input->absbit);
	set_bit(BTN_C, input->keybit);
	set_bit(BTN_Z, input->keybit);
	set_bit(INPUT_PROP_ACCELEROMETER, input->propbit);

	input_set_abs_params(input, ABS_X, 0xff, 0xff, 0, 0);
	input_set_abs_params(input, ABS_Y, 0xff, 0xff, 0, 0);

	/*
	 * Accelerometer measurements are noisy, so we need a bit of tolerance. In
	 * addition, the neutral position is not 0, so we estimate it here.
	 */
	input_set_abs_params(input, ABS_RX, 0x3ff, 0x3ff, 20, 735);
	input_set_abs_params(input, ABS_RY, 0x3ff, 0x3ff, 20, 515);
	input_set_abs_params(input, ABS_RZ, 0x3ff, 0x3ff, 20, 560);

	polled_input->poll = nunchuk_poll;
	polled_input->poll_interval = NUNCHUK_POLL_INTERVAL;

	/* Nunchuk handshake */
	buf[0] = 0xf0;
	buf[1] = 0x55;
	status = i2c_master_send(client, buf, 2);
	if (status < 0) {
		goto exit_polled_device;
	}

	udelay(1);

	buf[0] = 0xfb;
	buf[1] = 0x00;
	status = i2c_master_send(client, buf, 2);
	if (status < 0) {
		goto exit_polled_device;
	}

	/* Finally, register the input device; we're ready to go! */
	status = input_register_device(polled_input);
	if (status != 0) {
		goto exit_polled_device;
	}

	return 0;

exit_nunchuk_dev:
	devm_kfree(&client->dev, nunchuk);
exit_polled_device:
	input_free_device(polled_input);
exit:
	dev_err(&client->dev, "nunchuk bailed: 0x%x!\n", status);
	return status;
}

static int nunchuk_remove(struct i2c_client *client)
{
	struct nunchuk_dev *nunchuk;

	nunchuk = i2c_get_clientdata(client);
	input_unregister_device(nunchuk->polled_input);
	input_free_polled_device(nunchuk->polled_input);
	devm_kfree(&client->dev, nunchuk);

	return 0;
}

static const struct i2c_device_id nunchuk_id[] = {
	{"nunchuk", 0},
	{}
};
MODULE_DEVICE_TABLE(i2c, nunchuk_id);

#ifdef CONFIG_OF
static const struct of_device_id nunchuk_of_match[] = {
		{ .compatible = "nintendo,nunchuk" },
		{}
};
MODULE_DEVICE_TABLE(of, nunchuk_of_match);
#endif

static struct i2c_driver nunchuk_driver = {
	.driver = {
		.name = "nunchuk",
		.owner = THIS_MODULE,
		.of_match_table = nunchuk_of_match
	},
	.probe = nunchuk_probe,
	.remove = nunchuk_remove,
	.id_table = nunchuk_id
};

static int __init nunchuk_init(void)
{
	return i2c_add_driver(&nunchuk_driver);
}

static void __exit nunchuk_exit(void)
{
	i2c_del_driver(&nunchuk_driver);
}

module_init(nunchuk_init);
module_exit(nunchuk_exit);

MODULE_LICENSE("GPL");
