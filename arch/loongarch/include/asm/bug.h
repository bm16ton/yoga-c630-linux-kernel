/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __ASM_BUG_H
#define __ASM_BUG_H

<<<<<<< HEAD
#include <asm/break.h>
#include <linux/stringify.h>

#ifndef CONFIG_DEBUG_BUGVERBOSE
#define _BUGVERBOSE_LOCATION(file, line)
#else
#define __BUGVERBOSE_LOCATION(file, line)			\
		.pushsection .rodata.str, "aMS", @progbits, 1;	\
	10002:	.string file;					\
		.popsection;					\
								\
		.long 10002b - .;				\
		.short line;
#define _BUGVERBOSE_LOCATION(file, line) __BUGVERBOSE_LOCATION(file, line)
#endif

#ifndef CONFIG_GENERIC_BUG
#define __BUG_ENTRY(flags)
#else
#define __BUG_ENTRY(flags) 					\
		.pushsection __bug_table, "aw";			\
		.align 2;					\
	10000:	.long 10001f - .;				\
		_BUGVERBOSE_LOCATION(__FILE__, __LINE__)	\
		.short flags; 					\
		.popsection;					\
	10001:
#endif

#define ASM_BUG_FLAGS(flags)					\
	__BUG_ENTRY(flags)					\
	break		BRK_BUG

#define ASM_BUG()	ASM_BUG_FLAGS(0)

#define __BUG_FLAGS(flags)					\
	asm_inline volatile (__stringify(ASM_BUG_FLAGS(flags)));

#define __WARN_FLAGS(flags)					\
do {								\
	instrumentation_begin();				\
	__BUG_FLAGS(BUGFLAG_WARNING|(flags));			\
	instrumentation_end();					\
} while (0)

#define BUG()							\
do {								\
	instrumentation_begin();				\
	__BUG_FLAGS(0);						\
	unreachable();						\
} while (0)

#define HAVE_ARCH_BUG

=======
#include <linux/compiler.h>

#ifdef CONFIG_BUG

#include <asm/break.h>

static inline void __noreturn BUG(void)
{
	__asm__ __volatile__("break %0" : : "i" (BRK_BUG));
	unreachable();
}

#define HAVE_ARCH_BUG

#endif

>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
#include <asm-generic/bug.h>

#endif /* __ASM_BUG_H */
