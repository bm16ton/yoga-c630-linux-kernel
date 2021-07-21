#ifndef _HD44780_I2C_H_
#define _HD44780_I2C_H_

#define BUF_SIZE		64
#define ESC_SEQ_BUF_SIZE	4

struct hd44780i2c_geometry {
	int cols;
	int rows;
	int start_addrs[];
};

struct hd44780i2c {
	struct cdev cdev;
	struct device *device;
	struct i2c_client *i2c_client;
	struct hd44780i2c_geometry *geometry;

	/* Current cursor positon on the display */
	struct {
		int row;
		int col;
	} pos;

	char buf[BUF_SIZE];
	struct {
		char buf[ESC_SEQ_BUF_SIZE];
		int length;
	} esc_seq_buf;
	bool is_in_esc_seq;

	bool backlight;
	bool cursor_blink;
	bool cursor_display;

	bool dirty;

	struct mutex lock;
	struct list_head list;
};

void hd44780i2c_write(struct hd44780i2c *, const char *, size_t);
void hd44780i2c_init_lcd(struct hd44780i2c *);
void hd44780i2c_print(struct hd44780i2c *, const char *);
void hd44780i2c_flush(struct hd44780i2c *);
void hd44780i2c_set_geometry(struct hd44780i2c *, struct hd44780i2c_geometry *);
void hd44780i2c_set_backlight(struct hd44780i2c *, bool);
void hd44780i2c_set_cursor_blink(struct hd44780i2c *, bool);
void hd44780i2c_set_cursor_display(struct hd44780i2c *, bool);

extern struct hd44780i2c_geometry *hd44780i2c_geometries[];
#endif
