/* SPDX-License-Identifier: GPL-2.0 */
/*
 * powerpc KFENCE support.
 *
 * Copyright (C) 2020 CS GROUP France
 */

#ifndef __ASM_POWERPC_KFENCE_H
#define __ASM_POWERPC_KFENCE_H

#include <linux/mm.h>
#include <asm/pgtable.h>

<<<<<<< HEAD
#ifdef CONFIG_PPC64_ELF_ABI_V1
#define ARCH_FUNC_PREFIX "."
#endif

=======
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
static inline bool arch_kfence_init_pool(void)
{
	return true;
}

<<<<<<< HEAD
#ifdef CONFIG_PPC64
static inline bool kfence_protect_page(unsigned long addr, bool protect)
{
	struct page *page = virt_to_page(addr);

	__kernel_map_pages(page, 1, !protect);

	return true;
}
#else
=======
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
static inline bool kfence_protect_page(unsigned long addr, bool protect)
{
	pte_t *kpte = virt_to_kpte(addr);

	if (protect) {
		pte_update(&init_mm, addr, kpte, _PAGE_PRESENT, 0, 0);
		flush_tlb_kernel_range(addr, addr + PAGE_SIZE);
	} else {
		pte_update(&init_mm, addr, kpte, 0, _PAGE_PRESENT, 0);
	}

	return true;
}
<<<<<<< HEAD
#endif
=======
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2

#endif /* __ASM_POWERPC_KFENCE_H */
