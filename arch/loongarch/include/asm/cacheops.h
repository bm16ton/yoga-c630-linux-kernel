/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Cache operations for the cache instruction.
 *
 * Copyright (C) 2020-2022 Loongson Technology Corporation Limited
 */
#ifndef __ASM_CACHEOPS_H
#define __ASM_CACHEOPS_H

/*
<<<<<<< HEAD
 * Most cache ops are split into a 3 bit field identifying the cache, and a 2
 * bit field identifying the cache operation.
 */
#define CacheOp_Cache			0x07
#define CacheOp_Op			0x18

#define Cache_LEAF0			0x00
#define Cache_LEAF1			0x01
#define Cache_LEAF2			0x02
#define Cache_LEAF3			0x03
#define Cache_LEAF4			0x04
#define Cache_LEAF5			0x05
=======
 * Most cache ops are split into a 2 bit field identifying the cache, and a 3
 * bit field identifying the cache operation.
 */
#define CacheOp_Cache			0x03
#define CacheOp_Op			0x1c

#define Cache_I				0x00
#define Cache_D				0x01
#define Cache_V				0x02
#define Cache_S				0x03
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2

#define Index_Invalidate		0x08
#define Index_Writeback_Inv		0x08
#define Hit_Invalidate			0x10
#define Hit_Writeback_Inv		0x10
#define CacheOp_User_Defined		0x18

<<<<<<< HEAD
#define Index_Writeback_Inv_LEAF0	(Cache_LEAF0 | Index_Writeback_Inv)
#define Index_Writeback_Inv_LEAF1	(Cache_LEAF1 | Index_Writeback_Inv)
#define Index_Writeback_Inv_LEAF2	(Cache_LEAF2 | Index_Writeback_Inv)
#define Index_Writeback_Inv_LEAF3	(Cache_LEAF3 | Index_Writeback_Inv)
#define Index_Writeback_Inv_LEAF4	(Cache_LEAF4 | Index_Writeback_Inv)
#define Index_Writeback_Inv_LEAF5	(Cache_LEAF5 | Index_Writeback_Inv)
#define Hit_Writeback_Inv_LEAF0		(Cache_LEAF0 | Hit_Writeback_Inv)
#define Hit_Writeback_Inv_LEAF1		(Cache_LEAF1 | Hit_Writeback_Inv)
#define Hit_Writeback_Inv_LEAF2		(Cache_LEAF2 | Hit_Writeback_Inv)
#define Hit_Writeback_Inv_LEAF3		(Cache_LEAF3 | Hit_Writeback_Inv)
#define Hit_Writeback_Inv_LEAF4		(Cache_LEAF4 | Hit_Writeback_Inv)
#define Hit_Writeback_Inv_LEAF5		(Cache_LEAF5 | Hit_Writeback_Inv)
=======
#define Index_Invalidate_I		(Cache_I | Index_Invalidate)
#define Index_Writeback_Inv_D		(Cache_D | Index_Writeback_Inv)
#define Index_Writeback_Inv_V		(Cache_V | Index_Writeback_Inv)
#define Index_Writeback_Inv_S		(Cache_S | Index_Writeback_Inv)
#define Hit_Invalidate_I		(Cache_I | Hit_Invalidate)
#define Hit_Writeback_Inv_D		(Cache_D | Hit_Writeback_Inv)
#define Hit_Writeback_Inv_V		(Cache_V | Hit_Writeback_Inv)
#define Hit_Writeback_Inv_S		(Cache_S | Hit_Writeback_Inv)
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2

#endif	/* __ASM_CACHEOPS_H */
