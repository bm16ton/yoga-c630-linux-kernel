// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2020 Francis Laniel <laniel_francis@privacyrequired.com>
 *
 * Add tests related to fortified functions in this file.
 */
#include "lkdtm.h"
#include <linux/string.h>
#include <linux/slab.h>

static volatile int fortify_scratch_space;

<<<<<<< HEAD
static void lkdtm_FORTIFY_STR_OBJECT(void)
{
	struct target {
		char a[10];
		int foo;
	} target[3] = {};
=======
static void lkdtm_FORTIFIED_OBJECT(void)
{
	struct target {
		char a[10];
	} target[2] = {};
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
	/*
	 * Using volatile prevents the compiler from determining the value of
	 * 'size' at compile time. Without that, we would get a compile error
	 * rather than a runtime error.
	 */
<<<<<<< HEAD
	volatile int size = 20;

	pr_info("trying to strcmp() past the end of a struct\n");

	strncpy(target[0].a, target[1].a, size);

	/* Store result to global to prevent the code from being eliminated */
	fortify_scratch_space = target[0].a[3];

	pr_err("FAIL: fortify did not block a strncpy() object write overflow!\n");
	pr_expected_config(CONFIG_FORTIFY_SOURCE);
}

static void lkdtm_FORTIFY_STR_MEMBER(void)
=======
	volatile int size = 11;

	pr_info("trying to read past the end of a struct\n");

	/* Store result to global to prevent the code from being eliminated */
	fortify_scratch_space = memcmp(&target[0], &target[1], size);

	pr_err("FAIL: fortify did not block an object overread!\n");
	pr_expected_config(CONFIG_FORTIFY_SOURCE);
}

static void lkdtm_FORTIFIED_SUBOBJECT(void)
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
{
	struct target {
		char a[10];
		char b[10];
	} target;
	volatile int size = 20;
	char *src;

	src = kmalloc(size, GFP_KERNEL);
	strscpy(src, "over ten bytes", size);
	size = strlen(src) + 1;

<<<<<<< HEAD
	pr_info("trying to strncpy() past the end of a struct member...\n");
=======
	pr_info("trying to strncpy past the end of a member of a struct\n");
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2

	/*
	 * strncpy(target.a, src, 20); will hit a compile error because the
	 * compiler knows at build time that target.a < 20 bytes. Use a
	 * volatile to force a runtime error.
	 */
	strncpy(target.a, src, size);

	/* Store result to global to prevent the code from being eliminated */
	fortify_scratch_space = target.a[3];

<<<<<<< HEAD
	pr_err("FAIL: fortify did not block a strncpy() struct member write overflow!\n");
	pr_expected_config(CONFIG_FORTIFY_SOURCE);

	kfree(src);
}

static void lkdtm_FORTIFY_MEM_OBJECT(void)
{
	int before[10];
	struct target {
		char a[10];
		int foo;
	} target = {};
	int after[10];
	/*
	 * Using volatile prevents the compiler from determining the value of
	 * 'size' at compile time. Without that, we would get a compile error
	 * rather than a runtime error.
	 */
	volatile int size = 20;

	memset(before, 0, sizeof(before));
	memset(after, 0, sizeof(after));
	fortify_scratch_space = before[5];
	fortify_scratch_space = after[5];

	pr_info("trying to memcpy() past the end of a struct\n");

	pr_info("0: %zu\n", __builtin_object_size(&target, 0));
	pr_info("1: %zu\n", __builtin_object_size(&target, 1));
	pr_info("s: %d\n", size);
	memcpy(&target, &before, size);

	/* Store result to global to prevent the code from being eliminated */
	fortify_scratch_space = target.a[3];

	pr_err("FAIL: fortify did not block a memcpy() object write overflow!\n");
	pr_expected_config(CONFIG_FORTIFY_SOURCE);
}

static void lkdtm_FORTIFY_MEM_MEMBER(void)
{
	struct target {
		char a[10];
		char b[10];
	} target;
	volatile int size = 20;
	char *src;

	src = kmalloc(size, GFP_KERNEL);
	strscpy(src, "over ten bytes", size);
	size = strlen(src) + 1;

	pr_info("trying to memcpy() past the end of a struct member...\n");

	/*
	 * strncpy(target.a, src, 20); will hit a compile error because the
	 * compiler knows at build time that target.a < 20 bytes. Use a
	 * volatile to force a runtime error.
	 */
	memcpy(target.a, src, size);

	/* Store result to global to prevent the code from being eliminated */
	fortify_scratch_space = target.a[3];

	pr_err("FAIL: fortify did not block a memcpy() struct member write overflow!\n");
=======
	pr_err("FAIL: fortify did not block an sub-object overrun!\n");
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
	pr_expected_config(CONFIG_FORTIFY_SOURCE);

	kfree(src);
}

/*
 * Calls fortified strscpy to test that it returns the same result as vanilla
 * strscpy and generate a panic because there is a write overflow (i.e. src
 * length is greater than dst length).
 */
<<<<<<< HEAD
static void lkdtm_FORTIFY_STRSCPY(void)
=======
static void lkdtm_FORTIFIED_STRSCPY(void)
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
{
	char *src;
	char dst[5];

	struct {
		union {
			char big[10];
			char src[5];
		};
	} weird = { .big = "hello!" };
	char weird_dst[sizeof(weird.src) + 1];

	src = kstrdup("foobar", GFP_KERNEL);

	if (src == NULL)
		return;

	/* Vanilla strscpy returns -E2BIG if size is 0. */
	if (strscpy(dst, src, 0) != -E2BIG)
		pr_warn("FAIL: strscpy() of 0 length did not return -E2BIG\n");

	/* Vanilla strscpy returns -E2BIG if src is truncated. */
	if (strscpy(dst, src, sizeof(dst)) != -E2BIG)
		pr_warn("FAIL: strscpy() did not return -E2BIG while src is truncated\n");

	/* After above call, dst must contain "foob" because src was truncated. */
	if (strncmp(dst, "foob", sizeof(dst)) != 0)
		pr_warn("FAIL: after strscpy() dst does not contain \"foob\" but \"%s\"\n",
			dst);

	/* Shrink src so the strscpy() below succeeds. */
	src[3] = '\0';

	/*
	 * Vanilla strscpy returns number of character copied if everything goes
	 * well.
	 */
	if (strscpy(dst, src, sizeof(dst)) != 3)
		pr_warn("FAIL: strscpy() did not return 3 while src was copied entirely truncated\n");

	/* After above call, dst must contain "foo" because src was copied. */
	if (strncmp(dst, "foo", sizeof(dst)) != 0)
		pr_warn("FAIL: after strscpy() dst does not contain \"foo\" but \"%s\"\n",
			dst);

	/* Test when src is embedded inside a union. */
	strscpy(weird_dst, weird.src, sizeof(weird_dst));

	if (strcmp(weird_dst, "hello") != 0)
		pr_warn("FAIL: after strscpy() weird_dst does not contain \"hello\" but \"%s\"\n",
			weird_dst);

	/* Restore src to its initial value. */
	src[3] = 'b';

	/*
	 * Use strlen here so size cannot be known at compile time and there is
	 * a runtime write overflow.
	 */
	strscpy(dst, src, strlen(src));

	pr_err("FAIL: strscpy() overflow not detected!\n");
	pr_expected_config(CONFIG_FORTIFY_SOURCE);

	kfree(src);
}

static struct crashtype crashtypes[] = {
<<<<<<< HEAD
	CRASHTYPE(FORTIFY_STR_OBJECT),
	CRASHTYPE(FORTIFY_STR_MEMBER),
	CRASHTYPE(FORTIFY_MEM_OBJECT),
	CRASHTYPE(FORTIFY_MEM_MEMBER),
	CRASHTYPE(FORTIFY_STRSCPY),
=======
	CRASHTYPE(FORTIFIED_OBJECT),
	CRASHTYPE(FORTIFIED_SUBOBJECT),
	CRASHTYPE(FORTIFIED_STRSCPY),
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
};

struct crashtype_category fortify_crashtypes = {
	.crashtypes = crashtypes,
	.len	    = ARRAY_SIZE(crashtypes),
};
