/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright 2006 PathScale, Inc.  All Rights Reserved.
 */

#include <linux/linkage.h>

/*
 * override generic version in lib/iomap_copy.c
 */
SYM_FUNC_START(__iowrite32_copy)
	movl %edx,%ecx
<<<<<<< HEAD
	rep movsl
=======
	rep movsd
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
	RET
SYM_FUNC_END(__iowrite32_copy)
