// SPDX-License-Identifier: GPL-2.0-or-later
/* 
 *    PDC early console support - use PDC firmware to dump text via boot console
 *
 *    Copyright (C) 2001-2022 Helge Deller <deller@gmx.de>
 */

#include <linux/console.h>
#include <linux/init.h>
#include <linux/serial_core.h>
#include <linux/kgdb.h>
#include <asm/page.h>		/* for PAGE0 */
#include <asm/pdc.h>		/* for iodc_call() proto and friends */

static void pdc_console_write(struct console *co, const char *s, unsigned count)
{
	int i = 0;

	do {
		i += pdc_iodc_print(s + i, count - i);
	} while (i < count);
}

#ifdef CONFIG_KGDB
static int kgdb_pdc_read_char(void)
{
	int c = pdc_iodc_getc();

<<<<<<< HEAD
	return (c <= 0) ? NO_POLL_CHAR : c;
}

static void kgdb_pdc_write_char(u8 chr)
{
	/* no need to print char as it's shown on standard console */
	/* pdc_iodc_print(&chr, 1); */
}

static struct kgdb_io kgdb_pdc_io_ops = {
	.name = "kgdb_pdc",
	.read_char = kgdb_pdc_read_char,
	.write_char = kgdb_pdc_write_char,
};
=======
static unsigned int pdc_console_tty_write_room(struct tty_struct *tty)
{
	return 32768; /* no limit, no buffer used */
}

static const struct tty_operations pdc_console_tty_ops = {
	.open = pdc_console_tty_open,
	.close = pdc_console_tty_close,
	.write = pdc_console_tty_write,
	.write_room = pdc_console_tty_write_room,
};

static void pdc_console_poll(struct timer_list *unused)
{
	int data, count = 0;

	while (1) {
		data = pdc_console_poll_key(NULL);
		if (data == -1)
			break;
		tty_insert_flip_char(&tty_port, data & 0xFF, TTY_NORMAL);
		count ++;
	}

	if (count)
		tty_flip_buffer_push(&tty_port);

	if (pdc_cons.flags & CON_ENABLED)
		mod_timer(&pdc_console_timer, jiffies + PDC_CONS_POLL_DELAY);
}

static struct tty_driver *pdc_console_tty_driver;

static int __init pdc_console_tty_driver_init(void)
{
	struct tty_driver *driver;
	int err;

	/* Check if the console driver is still registered.
	 * It is unregistered if the pdc console was not selected as the
	 * primary console. */

	struct console *tmp;

	console_lock();
	for_each_console(tmp)
		if (tmp == &pdc_cons)
			break;
	console_unlock();

	if (!tmp) {
		printk(KERN_INFO "PDC console driver not registered anymore, not creating %s\n", pdc_cons.name);
		return -ENODEV;
	}

	printk(KERN_INFO "The PDC console driver is still registered, removing CON_BOOT flag\n");
	pdc_cons.flags &= ~CON_BOOT;

	driver = tty_alloc_driver(1, TTY_DRIVER_REAL_RAW |
			TTY_DRIVER_RESET_TERMIOS);
	if (IS_ERR(driver))
		return PTR_ERR(driver);

	tty_port_init(&tty_port);

	driver->driver_name = "pdc_cons";
	driver->name = "ttyB";
	driver->major = MUX_MAJOR;
	driver->minor_start = 0;
	driver->type = TTY_DRIVER_TYPE_SYSTEM;
	driver->init_termios = tty_std_termios;
	tty_set_operations(driver, &pdc_console_tty_ops);
	tty_port_link_device(&tty_port, driver, 0);

	err = tty_register_driver(driver);
	if (err) {
		printk(KERN_ERR "Unable to register the PDC console TTY driver\n");
		tty_port_destroy(&tty_port);
		tty_driver_kref_put(driver);
		return err;
	}

	pdc_console_tty_driver = driver;

	return 0;
}
device_initcall(pdc_console_tty_driver_init);

static struct tty_driver * pdc_console_device (struct console *c, int *index)
{
	*index = c->index;
	return pdc_console_tty_driver;
}
#else
#define pdc_console_device NULL
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
#endif

static int __init pdc_earlycon_setup(struct earlycon_device *device,
				     const char *opt)
{
	struct console *earlycon_console;

	/* If the console is duplex then copy the COUT parameters to CIN. */
	if (PAGE0->mem_cons.cl_class == CL_DUPLEX)
		memcpy(&PAGE0->mem_kbd, &PAGE0->mem_cons, sizeof(PAGE0->mem_cons));

	earlycon_console = device->con;
	earlycon_console->write = pdc_console_write;
	device->port.iotype = UPIO_MEM32BE;

#ifdef CONFIG_KGDB
	kgdb_register_io_module(&kgdb_pdc_io_ops);
#endif

	return 0;
}

EARLYCON_DECLARE(pdc, pdc_earlycon_setup);
