/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2020-2022 Loongson Technology Corporation Limited
 */
#ifndef _ASM_LOONGARCH_EFI_H
#define _ASM_LOONGARCH_EFI_H

#include <linux/efi.h>

void __init efi_init(void);
void __init efi_runtime_init(void);
void efifb_setup_from_dmi(struct screen_info *si, const char *opt);

#define ARCH_EFI_IRQ_FLAGS_MASK  0x00000004  /* Bit 2: CSR.CRMD.IE */

#define arch_efi_call_virt_setup()
#define arch_efi_call_virt_teardown()

#define EFI_ALLOC_ALIGN		SZ_64K
<<<<<<< HEAD
#define EFI_RT_VIRTUAL_OFFSET	CSR_DMW0_BASE

static inline struct screen_info *alloc_screen_info(void)
{
	return &screen_info;
}

static inline void free_screen_info(struct screen_info *si)
{
}
=======

struct screen_info *alloc_screen_info(void);
void free_screen_info(struct screen_info *si);
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2

static inline unsigned long efi_get_max_initrd_addr(unsigned long image_addr)
{
	return ULONG_MAX;
}

#endif /* _ASM_LOONGARCH_EFI_H */
