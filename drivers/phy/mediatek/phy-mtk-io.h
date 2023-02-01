/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2021 MediaTek Inc.
 *
 * Author: Chunfeng Yun <chunfeng.yun@mediatek.com>
 */

#ifndef __PHY_MTK_H__
#define __PHY_MTK_H__

<<<<<<< HEAD
#include <linux/bitfield.h>
=======
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
#include <linux/io.h>

static inline void mtk_phy_clear_bits(void __iomem *reg, u32 bits)
{
	u32 tmp = readl(reg);

	tmp &= ~bits;
	writel(tmp, reg);
}

static inline void mtk_phy_set_bits(void __iomem *reg, u32 bits)
{
	u32 tmp = readl(reg);

	tmp |= bits;
	writel(tmp, reg);
}

static inline void mtk_phy_update_bits(void __iomem *reg, u32 mask, u32 val)
{
	u32 tmp = readl(reg);

	tmp &= ~mask;
	tmp |= val & mask;
	writel(tmp, reg);
}

<<<<<<< HEAD
/* field @mask shall be constant and continuous */
#define mtk_phy_update_field(reg, mask, val) \
({ \
	typeof(mask) mask_ = (mask);	\
	mtk_phy_update_bits(reg, mask_, FIELD_PREP(mask_, val)); \
})

=======
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
#endif
