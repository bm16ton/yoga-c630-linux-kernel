/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Clang Control Flow Integrity (CFI) support.
 *
<<<<<<< HEAD
 * Copyright (C) 2022 Google LLC
=======
 * Copyright (C) 2021 Google LLC
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
 */
#ifndef _LINUX_CFI_H
#define _LINUX_CFI_H

<<<<<<< HEAD
#include <linux/bug.h>
#include <linux/module.h>

#ifdef CONFIG_CFI_CLANG
enum bug_trap_type report_cfi_failure(struct pt_regs *regs, unsigned long addr,
				      unsigned long *target, u32 type);

static inline enum bug_trap_type report_cfi_failure_noaddr(struct pt_regs *regs,
							   unsigned long addr)
{
	return report_cfi_failure(regs, addr, NULL, 0);
}

#ifdef CONFIG_ARCH_USES_CFI_TRAPS
bool is_cfi_trap(unsigned long addr);
#endif
#endif /* CONFIG_CFI_CLANG */

#ifdef CONFIG_MODULES
#ifdef CONFIG_ARCH_USES_CFI_TRAPS
void module_cfi_finalize(const Elf_Ehdr *hdr, const Elf_Shdr *sechdrs,
			 struct module *mod);
#else
static inline void module_cfi_finalize(const Elf_Ehdr *hdr,
				       const Elf_Shdr *sechdrs,
				       struct module *mod) {}
#endif /* CONFIG_ARCH_USES_CFI_TRAPS */
#endif /* CONFIG_MODULES */
=======
#ifdef CONFIG_CFI_CLANG
typedef void (*cfi_check_fn)(uint64_t id, void *ptr, void *diag);

/* Compiler-generated function in each module, and the kernel */
extern void __cfi_check(uint64_t id, void *ptr, void *diag);

/*
 * Force the compiler to generate a CFI jump table entry for a function
 * and store the jump table address to __cfi_jt_<function>.
 */
#define __CFI_ADDRESSABLE(fn, __attr) \
	const void *__cfi_jt_ ## fn __visible __attr = (void *)&fn

#ifdef CONFIG_CFI_CLANG_SHADOW

extern void cfi_module_add(struct module *mod, unsigned long base_addr);
extern void cfi_module_remove(struct module *mod, unsigned long base_addr);

#else

static inline void cfi_module_add(struct module *mod, unsigned long base_addr) {}
static inline void cfi_module_remove(struct module *mod, unsigned long base_addr) {}

#endif /* CONFIG_CFI_CLANG_SHADOW */

#else /* !CONFIG_CFI_CLANG */

#ifdef CONFIG_X86_KERNEL_IBT

#define __CFI_ADDRESSABLE(fn, __attr) \
	const void *__cfi_jt_ ## fn __visible __attr = (void *)&fn

#endif /* CONFIG_X86_KERNEL_IBT */

#endif /* CONFIG_CFI_CLANG */

#ifndef __CFI_ADDRESSABLE
#define __CFI_ADDRESSABLE(fn, __attr)
#endif
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2

#endif /* _LINUX_CFI_H */
