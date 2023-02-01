// SPDX-License-Identifier: GPL-2.0
#include <linux/ftrace.h>
#include <linux/tracepoint.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/rv.h>
#include <rv/instrumentation.h>
#include <rv/da_monitor.h>

#define MODULE_NAME "MODEL_NAME"

/*
 * XXX: include required tracepoint headers, e.g.,
 * #include <linux/trace/events/sched.h>
 */
#include <trace/events/rv.h>

/*
 * This is the self-generated part of the monitor. Generally, there is no need
 * to touch this section.
 */
#include "MODEL_NAME.h"

/*
 * Declare the deterministic automata monitor.
 *
 * The rv monitor reference is needed for the monitor declaration.
 */
<<<<<<< HEAD
static struct rv_monitor rv_MODEL_NAME;
=======
struct rv_monitor rv_MODEL_NAME;
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
DECLARE_DA_MON_PER_CPU(MODEL_NAME, MIN_TYPE);

/*
 * This is the instrumentation part of the monitor.
 *
 * This is the section where manual work is required. Here the kernel events
 * are translated into model's event.
 *
 */
TRACEPOINT_HANDLERS_SKEL
static int enable_MODEL_NAME(void)
{
	int retval;

	retval = da_monitor_init_MODEL_NAME();
	if (retval)
		return retval;

TRACEPOINT_ATTACH

	return 0;
}

static void disable_MODEL_NAME(void)
{
	rv_MODEL_NAME.enabled = 0;

TRACEPOINT_DETACH

	da_monitor_destroy_MODEL_NAME();
}

/*
 * This is the monitor register section.
 */
<<<<<<< HEAD
static struct rv_monitor rv_MODEL_NAME = {
=======
struct rv_monitor rv_MODEL_NAME = {
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
	.name = "MODEL_NAME",
	.description = "auto-generated MODEL_NAME",
	.enable = enable_MODEL_NAME,
	.disable = disable_MODEL_NAME,
	.reset = da_monitor_reset_all_MODEL_NAME,
	.enabled = 0,
};

<<<<<<< HEAD
static int __init register_MODEL_NAME(void)
=======
static int register_MODEL_NAME(void)
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
{
	rv_register_monitor(&rv_MODEL_NAME);
	return 0;
}

<<<<<<< HEAD
static void __exit unregister_MODEL_NAME(void)
=======
static void unregister_MODEL_NAME(void)
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
{
	rv_unregister_monitor(&rv_MODEL_NAME);
}

module_init(register_MODEL_NAME);
module_exit(unregister_MODEL_NAME);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("dot2k: auto-generated");
MODULE_DESCRIPTION("MODEL_NAME");
