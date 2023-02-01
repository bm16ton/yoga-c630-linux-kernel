/* SPDX-License-Identifier: GPL-2.0 */

/* Copyright (c) 2012-2018, The Linux Foundation. All rights reserved.
<<<<<<< HEAD
 * Copyright (C) 2018-2022 Linaro Ltd.
=======
 * Copyright (C) 2018-2021 Linaro Ltd.
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
 */
#ifndef _IPA_REG_H_
#define _IPA_REG_H_

#include <linux/bitfield.h>
#include <linux/bug.h>

#include "ipa_version.h"

struct ipa;

/**
 * DOC: IPA Registers
 *
 * IPA registers are located within the "ipa-reg" address space defined by
 * Device Tree.  Each register has a specified offset within that space,
 * which is mapped into virtual memory space in ipa_mem_init().  Each
 * has a unique identifer, taken from the ipa_reg_id enumerated type.
 * All IPA registers are 32 bits wide.
 *
 * Certain "parameterized" register types are duplicated for a number of
 * instances of something.  For example, each IPA endpoint has an set of
 * registers defining its configuration.  The offset to an endpoint's set
 * of registers is computed based on an "base" offset, plus an endpoint's
 * ID multiplied and a "stride" value for the register.  Similarly, some
 * registers have an offset that depends on execution environment.  In
 * this case, the stride is multiplied by a member of the gsi_ee_id
 * enumerated type.
 *
 * Each version of IPA implements an array of ipa_reg structures indexed
 * by register ID.  Each entry in the array specifies the base offset and
 * (for parameterized registers) a non-zero stride value.  Not all versions
 * of IPA define all registers.  The offset for a register is returned by
 * ipa_reg_offset() when the register's ipa_reg structure is supplied;
 * zero is returned for an undefined register (this should never happen).
 *
<<<<<<< HEAD
 * Some registers encode multiple fields within them.  Each field in
 * such a register has a unique identifier (from an enumerated type).
 * The position and width of the fields in a register are defined by
 * an array of field masks, indexed by field ID.  Two functions are
 * used to access register fields; both take an ipa_reg structure as
 * argument.  To encode a value to be represented in a register field,
 * the value and field ID are passed to ipa_reg_encode().  To extract
 * a value encoded in a register field, the field ID is passed to
 * ipa_reg_decode().  In addition, for single-bit fields, ipa_reg_bit()
 * can be used to either encode the bit value, or to generate a mask
 * used to extract the bit value.
 */

/* enum ipa_reg_id - IPA register IDs */
enum ipa_reg_id {
	COMP_CFG,
	CLKON_CFG,
	ROUTE,
	SHARED_MEM_SIZE,
	QSB_MAX_WRITES,
	QSB_MAX_READS,
	FILT_ROUT_HASH_EN,
	FILT_ROUT_HASH_FLUSH,
	STATE_AGGR_ACTIVE,
	IPA_BCR,					/* Not IPA v4.5+ */
	LOCAL_PKT_PROC_CNTXT,
	AGGR_FORCE_CLOSE,
	COUNTER_CFG,					/* Not IPA v4.5+ */
	IPA_TX_CFG,					/* IPA v3.5+ */
	FLAVOR_0,					/* IPA v3.5+ */
	IDLE_INDICATION_CFG,				/* IPA v3.5+ */
	QTIME_TIMESTAMP_CFG,				/* IPA v4.5+ */
	TIMERS_XO_CLK_DIV_CFG,				/* IPA v4.5+ */
	TIMERS_PULSE_GRAN_CFG,				/* IPA v4.5+ */
	SRC_RSRC_GRP_01_RSRC_TYPE,
	SRC_RSRC_GRP_23_RSRC_TYPE,
	SRC_RSRC_GRP_45_RSRC_TYPE,		/* Not IPA v3.5+, IPA v4.5 */
	SRC_RSRC_GRP_67_RSRC_TYPE,			/* Not IPA v3.5+ */
	DST_RSRC_GRP_01_RSRC_TYPE,
	DST_RSRC_GRP_23_RSRC_TYPE,
	DST_RSRC_GRP_45_RSRC_TYPE,		/* Not IPA v3.5+, IPA v4.5 */
	DST_RSRC_GRP_67_RSRC_TYPE,			/* Not IPA v3.5+ */
	ENDP_INIT_CTRL,		/* Not IPA v4.2+ for TX, not IPA v4.0+ for RX */
	ENDP_INIT_CFG,
	ENDP_INIT_NAT,			/* TX only */
	ENDP_INIT_HDR,
	ENDP_INIT_HDR_EXT,
	ENDP_INIT_HDR_METADATA_MASK,	/* RX only */
	ENDP_INIT_MODE,			/* TX only */
	ENDP_INIT_AGGR,
	ENDP_INIT_HOL_BLOCK_EN,		/* RX only */
	ENDP_INIT_HOL_BLOCK_TIMER,	/* RX only */
	ENDP_INIT_DEAGGR,		/* TX only */
	ENDP_INIT_RSRC_GRP,
	ENDP_INIT_SEQ,			/* TX only */
	ENDP_STATUS,
	ENDP_FILTER_ROUTER_HSH_CFG,			/* Not IPA v4.2 */
	/* The IRQ registers are only used for GSI_EE_AP */
	IPA_IRQ_STTS,
	IPA_IRQ_EN,
	IPA_IRQ_CLR,
	IPA_IRQ_UC,
	IRQ_SUSPEND_INFO,
	IRQ_SUSPEND_EN,					/* IPA v3.1+ */
	IRQ_SUSPEND_CLR,				/* IPA v3.1+ */
	IPA_REG_ID_COUNT,				/* Last; not an ID */
};
=======
 * The offset of a register dependent on endpoint ID is computed by a macro
 * that is supplied a parameter "ep", "txep", or "rxep".  A register with an
 * "ep" parameter is valid for any endpoint; a register with a "txep" or
 * "rxep" parameter is valid only for TX or RX endpoints, respectively.  The
 * "*ep" value is assumed to be less than the maximum valid endpoint ID
 * for the current hardware, and that will not exceed IPA_ENDPOINT_MAX.
 *
 * The offset of registers related to filter and route tables is computed
 * by a macro that is supplied a parameter "er".  The "er" represents an
 * endpoint ID for filters, or a route ID for routes.  For filters, the
 * endpoint ID must be less than IPA_ENDPOINT_MAX, but is further restricted
 * because not all endpoints support filtering.  For routes, the route ID
 * must be less than IPA_ROUTE_MAX.
 *
 * The offset of registers related to resource types is computed by a macro
 * that is supplied a parameter "rt".  The "rt" represents a resource type,
 * which is a member of the ipa_resource_type_src enumerated type for
 * source endpoint resources or the ipa_resource_type_dst enumerated type
 * for destination endpoint resources.
 *
 * Some registers encode multiple fields within them.  For these, each field
 * has a symbol below defining a field mask that encodes both the position
 * and width of the field within its register.
 *
 * In some cases, different versions of IPA hardware use different offset or
 * field mask values.  In such cases an inline_function(ipa) is used rather
 * than a MACRO to define the offset or field mask to use.
 *
 * Finally, some registers hold bitmasks representing endpoints.  In such
 * cases the @available field in the @ipa structure defines the "full" set
 * of valid bits for the register.
 */

#define IPA_REG_COMP_CFG_OFFSET				0x0000003c
/* The next field is not supported for IPA v4.0+, not present for IPA v4.5+ */
#define ENABLE_FMASK				GENMASK(0, 0)
/* The next field is present for IPA v4.7+ */
#define RAM_ARB_PRI_CLIENT_SAMP_FIX_DIS_FMASK	GENMASK(0, 0)
#define GSI_SNOC_BYPASS_DIS_FMASK		GENMASK(1, 1)
#define GEN_QMB_0_SNOC_BYPASS_DIS_FMASK		GENMASK(2, 2)
#define GEN_QMB_1_SNOC_BYPASS_DIS_FMASK		GENMASK(3, 3)
/* The next field is not present for IPA v4.5+ */
#define IPA_DCMP_FAST_CLK_EN_FMASK		GENMASK(4, 4)
/* The next twelve fields are present for IPA v4.0+ */
#define IPA_QMB_SELECT_CONS_EN_FMASK		GENMASK(5, 5)
#define IPA_QMB_SELECT_PROD_EN_FMASK		GENMASK(6, 6)
#define GSI_MULTI_INORDER_RD_DIS_FMASK		GENMASK(7, 7)
#define GSI_MULTI_INORDER_WR_DIS_FMASK		GENMASK(8, 8)
#define GEN_QMB_0_MULTI_INORDER_RD_DIS_FMASK	GENMASK(9, 9)
#define GEN_QMB_1_MULTI_INORDER_RD_DIS_FMASK	GENMASK(10, 10)
#define GEN_QMB_0_MULTI_INORDER_WR_DIS_FMASK	GENMASK(11, 11)
#define GEN_QMB_1_MULTI_INORDER_WR_DIS_FMASK	GENMASK(12, 12)
#define GEN_QMB_0_SNOC_CNOC_LOOP_PROT_DIS_FMASK	GENMASK(13, 13)
#define GSI_SNOC_CNOC_LOOP_PROT_DISABLE_FMASK	GENMASK(14, 14)
#define GSI_MULTI_AXI_MASTERS_DIS_FMASK		GENMASK(15, 15)
#define IPA_QMB_SELECT_GLOBAL_EN_FMASK		GENMASK(16, 16)
/* The next five fields are present for IPA v4.9+ */
#define QMB_RAM_RD_CACHE_DISABLE_FMASK		GENMASK(19, 19)
#define GENQMB_AOOOWR_FMASK			GENMASK(20, 20)
#define IF_OUT_OF_BUF_STOP_RESET_MASK_EN_FMASK	GENMASK(21, 21)
#define GEN_QMB_1_DYNAMIC_ASIZE_FMASK		GENMASK(30, 30)
#define GEN_QMB_0_DYNAMIC_ASIZE_FMASK		GENMASK(31, 31)

/* Encoded value for COMP_CFG register ATOMIC_FETCHER_ARB_LOCK_DIS field */
static inline u32 arbitration_lock_disable_encoded(enum ipa_version version,
						   u32 mask)
{
	WARN_ON(version < IPA_VERSION_4_0);

	if (version < IPA_VERSION_4_9)
		return u32_encode_bits(mask, GENMASK(20, 17));

	if (version == IPA_VERSION_4_9)
		return u32_encode_bits(mask, GENMASK(24, 22));

	return u32_encode_bits(mask, GENMASK(23, 22));
}

/* Encoded value for COMP_CFG register FULL_FLUSH_WAIT_RS_CLOSURE_EN field */
static inline u32 full_flush_rsc_closure_en_encoded(enum ipa_version version,
						    bool enable)
{
	u32 val = enable ? 1 : 0;

	WARN_ON(version < IPA_VERSION_4_5);

	if (version == IPA_VERSION_4_5 || version == IPA_VERSION_4_7)
		return u32_encode_bits(val, GENMASK(21, 21));

	return u32_encode_bits(val, GENMASK(17, 17));
}

#define IPA_REG_CLKON_CFG_OFFSET			0x00000044
#define RX_FMASK				GENMASK(0, 0)
#define PROC_FMASK				GENMASK(1, 1)
#define TX_WRAPPER_FMASK			GENMASK(2, 2)
#define MISC_FMASK				GENMASK(3, 3)
#define RAM_ARB_FMASK				GENMASK(4, 4)
#define FTCH_HPS_FMASK				GENMASK(5, 5)
#define FTCH_DPS_FMASK				GENMASK(6, 6)
#define HPS_FMASK				GENMASK(7, 7)
#define DPS_FMASK				GENMASK(8, 8)
#define RX_HPS_CMDQS_FMASK			GENMASK(9, 9)
#define HPS_DPS_CMDQS_FMASK			GENMASK(10, 10)
#define DPS_TX_CMDQS_FMASK			GENMASK(11, 11)
#define RSRC_MNGR_FMASK				GENMASK(12, 12)
#define CTX_HANDLER_FMASK			GENMASK(13, 13)
#define ACK_MNGR_FMASK				GENMASK(14, 14)
#define D_DCPH_FMASK				GENMASK(15, 15)
#define H_DCPH_FMASK				GENMASK(16, 16)
/* The next field is not present for IPA v4.5+ */
#define DCMP_FMASK				GENMASK(17, 17)
/* The next three fields are present for IPA v3.5+ */
#define NTF_TX_CMDQS_FMASK			GENMASK(18, 18)
#define TX_0_FMASK				GENMASK(19, 19)
#define TX_1_FMASK				GENMASK(20, 20)
/* The next field is present for IPA v3.5.1+ */
#define FNR_FMASK				GENMASK(21, 21)
/* The next eight fields are present for IPA v4.0+ */
#define QSB2AXI_CMDQ_L_FMASK			GENMASK(22, 22)
#define AGGR_WRAPPER_FMASK			GENMASK(23, 23)
#define RAM_SLAVEWAY_FMASK			GENMASK(24, 24)
#define QMB_FMASK				GENMASK(25, 25)
#define WEIGHT_ARB_FMASK			GENMASK(26, 26)
#define GSI_IF_FMASK				GENMASK(27, 27)
#define GLOBAL_FMASK				GENMASK(28, 28)
#define GLOBAL_2X_CLK_FMASK			GENMASK(29, 29)
/* The next field is present for IPA v4.5+ */
#define DPL_FIFO_FMASK				GENMASK(30, 30)
/* The next field is present for IPA v4.7+ */
#define DRBIP_FMASK				GENMASK(31, 31)

#define IPA_REG_ROUTE_OFFSET				0x00000048
#define ROUTE_DIS_FMASK				GENMASK(0, 0)
#define ROUTE_DEF_PIPE_FMASK			GENMASK(5, 1)
#define ROUTE_DEF_HDR_TABLE_FMASK		GENMASK(6, 6)
#define ROUTE_DEF_HDR_OFST_FMASK		GENMASK(16, 7)
#define ROUTE_FRAG_DEF_PIPE_FMASK		GENMASK(21, 17)
#define ROUTE_DEF_RETAIN_HDR_FMASK		GENMASK(24, 24)

#define IPA_REG_SHARED_MEM_SIZE_OFFSET			0x00000054
#define SHARED_MEM_SIZE_FMASK			GENMASK(15, 0)
#define SHARED_MEM_BADDR_FMASK			GENMASK(31, 16)

#define IPA_REG_QSB_MAX_WRITES_OFFSET			0x00000074
#define GEN_QMB_0_MAX_WRITES_FMASK		GENMASK(3, 0)
#define GEN_QMB_1_MAX_WRITES_FMASK		GENMASK(7, 4)

#define IPA_REG_QSB_MAX_READS_OFFSET			0x00000078
#define GEN_QMB_0_MAX_READS_FMASK		GENMASK(3, 0)
#define GEN_QMB_1_MAX_READS_FMASK		GENMASK(7, 4)
/* The next two fields are present for IPA v4.0+ */
#define GEN_QMB_0_MAX_READS_BEATS_FMASK		GENMASK(23, 16)
#define GEN_QMB_1_MAX_READS_BEATS_FMASK		GENMASK(31, 24)

static inline u32 ipa_reg_filt_rout_hash_en_offset(enum ipa_version version)
{
	if (version < IPA_VERSION_4_0)
		return 0x000008c;
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2

/**
 * struct ipa_reg - An IPA register descriptor
 * @offset:	Register offset relative to base of the "ipa-reg" memory
 * @stride:	Distance between two instances, if parameterized
 * @fcount:	Number of entries in the @fmask array
 * @fmask:	Array of mask values defining position and width of fields
 * @name:	Upper-case name of the IPA register
 */
struct ipa_reg {
	u32 offset;
	u32 stride;
	u32 fcount;
	const u32 *fmask;			/* BIT(nr) or GENMASK(h, l) */
	const char *name;
};

<<<<<<< HEAD
/* Helper macro for defining "simple" (non-parameterized) registers */
#define IPA_REG(__NAME, __reg_id, __offset)				\
	IPA_REG_STRIDE(__NAME, __reg_id, __offset, 0)
=======
static inline u32 ipa_reg_filt_rout_hash_flush_offset(enum ipa_version version)
{
	if (version < IPA_VERSION_4_0)
		return 0x0000090;
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2

/* Helper macro for defining parameterized registers, specifying stride */
#define IPA_REG_STRIDE(__NAME, __reg_id, __offset, __stride)		\
	static const struct ipa_reg ipa_reg_ ## __reg_id = {		\
		.name	= #__NAME,					\
		.offset	= __offset,					\
		.stride	= __stride,					\
	}

#define IPA_REG_FIELDS(__NAME, __name, __offset)			\
	IPA_REG_STRIDE_FIELDS(__NAME, __name, __offset, 0)

<<<<<<< HEAD
#define IPA_REG_STRIDE_FIELDS(__NAME, __name, __offset, __stride)	\
	static const struct ipa_reg ipa_reg_ ## __name = {		\
		.name   = #__NAME,					\
		.offset = __offset,					\
		.stride = __stride,					\
		.fcount = ARRAY_SIZE(ipa_reg_ ## __name ## _fmask),	\
		.fmask  = ipa_reg_ ## __name ## _fmask,			\
	}
=======
/* ipa->available defines the valid bits in the STATE_AGGR_ACTIVE register */
static inline u32 ipa_reg_state_aggr_active_offset(enum ipa_version version)
{
	if (version < IPA_VERSION_4_0)
		return 0x0000010c;
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2

/**
 * struct ipa_regs - Description of registers supported by hardware
 * @reg_count:	Number of registers in the @reg[] array
 * @reg:		Array of register descriptors
 */
struct ipa_regs {
	u32 reg_count;
	const struct ipa_reg **reg;
};

<<<<<<< HEAD
/* COMP_CFG register */
enum ipa_reg_comp_cfg_field_id {
	COMP_CFG_ENABLE,				/* Not IPA v4.0+ */
	RAM_ARB_PRI_CLIENT_SAMP_FIX_DIS,		/* IPA v4.7+ */
	GSI_SNOC_BYPASS_DIS,
	GEN_QMB_0_SNOC_BYPASS_DIS,
	GEN_QMB_1_SNOC_BYPASS_DIS,
	IPA_DCMP_FAST_CLK_EN,				/* Not IPA v4.5+ */
	IPA_QMB_SELECT_CONS_EN,				/* IPA v4.0+ */
	IPA_QMB_SELECT_PROD_EN,				/* IPA v4.0+ */
	GSI_MULTI_INORDER_RD_DIS,			/* IPA v4.0+ */
	GSI_MULTI_INORDER_WR_DIS,			/* IPA v4.0+ */
	GEN_QMB_0_MULTI_INORDER_RD_DIS,			/* IPA v4.0+ */
	GEN_QMB_1_MULTI_INORDER_RD_DIS,			/* IPA v4.0+ */
	GEN_QMB_0_MULTI_INORDER_WR_DIS,			/* IPA v4.0+ */
	GEN_QMB_1_MULTI_INORDER_WR_DIS,			/* IPA v4.0+ */
	GEN_QMB_0_SNOC_CNOC_LOOP_PROT_DIS,		/* IPA v4.0+ */
	GSI_SNOC_CNOC_LOOP_PROT_DISABLE,		/* IPA v4.0+ */
	GSI_MULTI_AXI_MASTERS_DIS,			/* IPA v4.0+ */
	IPA_QMB_SELECT_GLOBAL_EN,			/* IPA v4.0+ */
	QMB_RAM_RD_CACHE_DISABLE,			/* IPA v4.9+ */
	GENQMB_AOOOWR,					/* IPA v4.9+ */
	IF_OUT_OF_BUF_STOP_RESET_MASK_EN,		/* IPA v4.9+ */
	GEN_QMB_1_DYNAMIC_ASIZE,			/* IPA v4.9+ */
	GEN_QMB_0_DYNAMIC_ASIZE,			/* IPA v4.9+ */
	ATOMIC_FETCHER_ARB_LOCK_DIS,			/* IPA v4.0+ */
	FULL_FLUSH_WAIT_RS_CLOSURE_EN,			/* IPA v4.5+ */
};

/* CLKON_CFG register */
enum ipa_reg_clkon_cfg_field_id {
	CLKON_RX,
	CLKON_PROC,
	TX_WRAPPER,
	CLKON_MISC,
	RAM_ARB,
	FTCH_HPS,
	FTCH_DPS,
	CLKON_HPS,
	CLKON_DPS,
	RX_HPS_CMDQS,
	HPS_DPS_CMDQS,
	DPS_TX_CMDQS,
	RSRC_MNGR,
	CTX_HANDLER,
	ACK_MNGR,
	D_DCPH,
	H_DCPH,
	CLKON_DCMP,					/* IPA v4.5+ */
	NTF_TX_CMDQS,					/* IPA v3.5+ */
	CLKON_TX_0,					/* IPA v3.5+ */
	CLKON_TX_1,					/* IPA v3.5+ */
	CLKON_FNR,					/* IPA v3.5.1+ */
	QSB2AXI_CMDQ_L,					/* IPA v4.0+ */
	AGGR_WRAPPER,					/* IPA v4.0+ */
	RAM_SLAVEWAY,					/* IPA v4.0+ */
	CLKON_QMB,					/* IPA v4.0+ */
	WEIGHT_ARB,					/* IPA v4.0+ */
	GSI_IF,						/* IPA v4.0+ */
	CLKON_GLOBAL,					/* IPA v4.0+ */
	GLOBAL_2X_CLK,					/* IPA v4.0+ */
	DPL_FIFO,					/* IPA v4.5+ */
	DRBIP,						/* IPA v4.7+ */
};
=======
/* The next register is not present for IPA v4.5+ */
#define IPA_REG_BCR_OFFSET				0x000001d0
/* The next two fields are not present for IPA v4.2+ */
#define BCR_CMDQ_L_LACK_ONE_ENTRY_FMASK		GENMASK(0, 0)
#define BCR_TX_NOT_USING_BRESP_FMASK		GENMASK(1, 1)
/* The next field is invalid for IPA v4.0+ */
#define BCR_TX_SUSPEND_IRQ_ASSERT_ONCE_FMASK	GENMASK(2, 2)
/* The next two fields are not present for IPA v4.2+ */
#define BCR_SUSPEND_L2_IRQ_FMASK		GENMASK(3, 3)
#define BCR_HOLB_DROP_L2_IRQ_FMASK		GENMASK(4, 4)
/* The next five fields are present for IPA v3.5+ */
#define BCR_DUAL_TX_FMASK			GENMASK(5, 5)
#define BCR_ENABLE_FILTER_DATA_CACHE_FMASK	GENMASK(6, 6)
#define BCR_NOTIF_PRIORITY_OVER_ZLT_FMASK	GENMASK(7, 7)
#define BCR_FILTER_PREFETCH_EN_FMASK		GENMASK(8, 8)
#define BCR_ROUTER_PREFETCH_EN_FMASK		GENMASK(9, 9)

/* The value of the next register must be a multiple of 8 (bottom 3 bits 0) */
#define IPA_REG_LOCAL_PKT_PROC_CNTXT_OFFSET		0x000001e8

/* Encoded value for LOCAL_PKT_PROC_CNTXT register BASE_ADDR field */
static inline u32 proc_cntxt_base_addr_encoded(enum ipa_version version,
					       u32 addr)
{
	if (version < IPA_VERSION_4_5)
		return u32_encode_bits(addr, GENMASK(16, 0));

	return u32_encode_bits(addr, GENMASK(17, 0));
}
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2

/* ROUTE register */
enum ipa_reg_route_field_id {
	ROUTE_DIS,
	ROUTE_DEF_PIPE,
	ROUTE_DEF_HDR_TABLE,
	ROUTE_DEF_HDR_OFST,
	ROUTE_FRAG_DEF_PIPE,
	ROUTE_DEF_RETAIN_HDR,
};

<<<<<<< HEAD
/* SHARED_MEM_SIZE register */
enum ipa_reg_shared_mem_size_field_id {
	MEM_SIZE,
	MEM_BADDR,
};

/* QSB_MAX_WRITES register */
enum ipa_reg_qsb_max_writes_field_id {
	GEN_QMB_0_MAX_WRITES,
	GEN_QMB_1_MAX_WRITES,
};

/* QSB_MAX_READS register */
enum ipa_reg_qsb_max_reads_field_id {
	GEN_QMB_0_MAX_READS,
	GEN_QMB_1_MAX_READS,
	GEN_QMB_0_MAX_READS_BEATS,			/* IPA v4.0+ */
	GEN_QMB_1_MAX_READS_BEATS,			/* IPA v4.0+ */
};

/* FILT_ROUT_HASH_EN and FILT_ROUT_HASH_FLUSH registers */
enum ipa_reg_rout_hash_field_id {
	IPV6_ROUTER_HASH,
	IPV6_FILTER_HASH,
	IPV4_ROUTER_HASH,
	IPV4_FILTER_HASH,
};
=======
/* The next register is not present for IPA v4.5+ */
#define IPA_REG_COUNTER_CFG_OFFSET			0x000001f0
/* The next field is not present for IPA v3.5+ */
#define EOT_COAL_GRANULARITY			GENMASK(3, 0)
#define AGGR_GRANULARITY_FMASK			GENMASK(8, 4)

/* The next register is present for IPA v3.5+ */
#define IPA_REG_TX_CFG_OFFSET				0x000001fc
/* The next three fields are not present for IPA v4.0+ */
#define TX0_PREFETCH_DISABLE_FMASK		GENMASK(0, 0)
#define TX1_PREFETCH_DISABLE_FMASK		GENMASK(1, 1)
#define PREFETCH_ALMOST_EMPTY_SIZE_FMASK	GENMASK(4, 2)
/* The next six fields are present for IPA v4.0+ */
#define PREFETCH_ALMOST_EMPTY_SIZE_TX0_FMASK	GENMASK(5, 2)
#define DMAW_SCND_OUTSD_PRED_THRESHOLD_FMASK	GENMASK(9, 6)
#define DMAW_SCND_OUTSD_PRED_EN_FMASK		GENMASK(10, 10)
#define DMAW_MAX_BEATS_256_DIS_FMASK		GENMASK(11, 11)
#define PA_MASK_EN_FMASK			GENMASK(12, 12)
#define PREFETCH_ALMOST_EMPTY_SIZE_TX1_FMASK	GENMASK(16, 13)
/* The next field is present for IPA v4.5+ */
#define DUAL_TX_ENABLE_FMASK			GENMASK(17, 17)
/* The next field is present for IPA v4.2+, but not IPA v4.5 */
#define SSPND_PA_NO_START_STATE_FMASK		GENMASK(18, 18)
/* The next field is present for IPA v4.2 only */
#define SSPND_PA_NO_BQ_STATE_FMASK		GENMASK(19, 19)

/* The next register is present for IPA v3.5+ */
#define IPA_REG_FLAVOR_0_OFFSET				0x00000210
#define IPA_MAX_PIPES_FMASK			GENMASK(3, 0)
#define IPA_MAX_CONS_PIPES_FMASK		GENMASK(12, 8)
#define IPA_MAX_PROD_PIPES_FMASK		GENMASK(20, 16)
#define IPA_PROD_LOWEST_FMASK			GENMASK(27, 24)

/* The next register is present for IPA v3.5+ */
static inline u32 ipa_reg_idle_indication_cfg_offset(enum ipa_version version)
{
	if (version >= IPA_VERSION_4_2)
		return 0x00000240;
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2

/* BCR register */
enum ipa_bcr_compat {
	BCR_CMDQ_L_LACK_ONE_ENTRY		= 0x0,	/* Not IPA v4.2+ */
	BCR_TX_NOT_USING_BRESP			= 0x1,	/* Not IPA v4.2+ */
	BCR_TX_SUSPEND_IRQ_ASSERT_ONCE		= 0x2,	/* Not IPA v4.0+ */
	BCR_SUSPEND_L2_IRQ			= 0x3,	/* Not IPA v4.2+ */
	BCR_HOLB_DROP_L2_IRQ			= 0x4,	/* Not IPA v4.2+ */
	BCR_DUAL_TX				= 0x5,	/* IPA v3.5+ */
	BCR_ENABLE_FILTER_DATA_CACHE		= 0x6,	/* IPA v3.5+ */
	BCR_NOTIF_PRIORITY_OVER_ZLT		= 0x7,	/* IPA v3.5+ */
	BCR_FILTER_PREFETCH_EN			= 0x8,	/* IPA v3.5+ */
	BCR_ROUTER_PREFETCH_EN			= 0x9,	/* IPA v3.5+ */
};

/* LOCAL_PKT_PROC_CNTXT register */
enum ipa_reg_local_pkt_proc_cntxt_field_id {
	IPA_BASE_ADDR,
};

/* COUNTER_CFG register */
enum ipa_reg_counter_cfg_field_id {
	EOT_COAL_GRANULARITY,				/* Not v3.5+ */
	AGGR_GRANULARITY,
};

/* IPA_TX_CFG register */
enum ipa_reg_ipa_tx_cfg_field_id {
	TX0_PREFETCH_DISABLE,				/* Not v4.0+ */
	TX1_PREFETCH_DISABLE,				/* Not v4.0+ */
	PREFETCH_ALMOST_EMPTY_SIZE,			/* Not v4.0+ */
	PREFETCH_ALMOST_EMPTY_SIZE_TX0,			/* v4.0+ */
	DMAW_SCND_OUTSD_PRED_THRESHOLD,			/* v4.0+ */
	DMAW_SCND_OUTSD_PRED_EN,			/* v4.0+ */
	DMAW_MAX_BEATS_256_DIS,				/* v4.0+ */
	PA_MASK_EN,					/* v4.0+ */
	PREFETCH_ALMOST_EMPTY_SIZE_TX1,			/* v4.0+ */
	DUAL_TX_ENABLE,					/* v4.5+ */
	SSPND_PA_NO_START_STATE,			/* v4,2+, not v4.5 */
	SSPND_PA_NO_BQ_STATE,				/* v4.2 only */
};

<<<<<<< HEAD
/* FLAVOR_0 register */
enum ipa_reg_flavor_0_field_id {
	MAX_PIPES,
	MAX_CONS_PIPES,
	MAX_PROD_PIPES,
	PROD_LOWEST,
};

/* IDLE_INDICATION_CFG register */
enum ipa_reg_idle_indication_cfg_field_id {
	ENTER_IDLE_DEBOUNCE_THRESH,
	CONST_NON_IDLE_ENABLE,
};

/* QTIME_TIMESTAMP_CFG register */
enum ipa_reg_qtime_timestamp_cfg_field_id {
	DPL_TIMESTAMP_LSB,
	DPL_TIMESTAMP_SEL,
	TAG_TIMESTAMP_LSB,
	NAT_TIMESTAMP_LSB,
};

/* TIMERS_XO_CLK_DIV_CFG register */
enum ipa_reg_timers_xo_clk_div_cfg_field_id {
	DIV_VALUE,
	DIV_ENABLE,
};

/* TIMERS_PULSE_GRAN_CFG register */
enum ipa_reg_timers_pulse_gran_cfg_field_id {
	PULSE_GRAN_0,
	PULSE_GRAN_1,
	PULSE_GRAN_2,
};

/* Values for IPA_GRAN_x fields of TIMERS_PULSE_GRAN_CFG */
=======
#define ENTER_IDLE_DEBOUNCE_THRESH_FMASK	GENMASK(15, 0)
#define CONST_NON_IDLE_ENABLE_FMASK		GENMASK(16, 16)

/* The next register is present for IPA v4.5+ */
#define IPA_REG_QTIME_TIMESTAMP_CFG_OFFSET		0x0000024c
#define DPL_TIMESTAMP_LSB_FMASK			GENMASK(4, 0)
#define DPL_TIMESTAMP_SEL_FMASK			GENMASK(7, 7)
#define TAG_TIMESTAMP_LSB_FMASK			GENMASK(12, 8)
#define NAT_TIMESTAMP_LSB_FMASK			GENMASK(20, 16)

/* The next register is present for IPA v4.5+ */
#define IPA_REG_TIMERS_XO_CLK_DIV_CFG_OFFSET		0x00000250
#define DIV_VALUE_FMASK				GENMASK(8, 0)
#define DIV_ENABLE_FMASK			GENMASK(31, 31)

/* The next register is present for IPA v4.5+ */
#define IPA_REG_TIMERS_PULSE_GRAN_CFG_OFFSET		0x00000254
#define GRAN_0_FMASK				GENMASK(2, 0)
#define GRAN_1_FMASK				GENMASK(5, 3)
#define GRAN_2_FMASK				GENMASK(8, 6)
/* Values for GRAN_x fields of TIMERS_PULSE_GRAN_CFG */
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
enum ipa_pulse_gran {
	IPA_GRAN_10_US				= 0x0,
	IPA_GRAN_20_US				= 0x1,
	IPA_GRAN_50_US				= 0x2,
	IPA_GRAN_100_US				= 0x3,
	IPA_GRAN_1_MS				= 0x4,
	IPA_GRAN_10_MS				= 0x5,
	IPA_GRAN_100_MS				= 0x6,
	IPA_GRAN_655350_US			= 0x7,
};

<<<<<<< HEAD
/* {SRC,DST}_RSRC_GRP_{01,23,45,67}_RSRC_TYPE registers */
enum ipa_reg_rsrc_grp_rsrc_type_field_id {
	X_MIN_LIM,
	X_MAX_LIM,
	Y_MIN_LIM,
	Y_MAX_LIM,
};

/* ENDP_INIT_CTRL register */
enum ipa_reg_endp_init_ctrl_field_id {
	ENDP_SUSPEND,					/* Not v4.0+ */
	ENDP_DELAY,					/* Not v4.2+ */
};

/* ENDP_INIT_CFG register */
enum ipa_reg_endp_init_cfg_field_id {
	FRAG_OFFLOAD_EN,
	CS_OFFLOAD_EN,
	CS_METADATA_HDR_OFFSET,
	CS_GEN_QMB_MASTER_SEL,
};

/** enum ipa_cs_offload_en - ENDP_INIT_CFG register CS_OFFLOAD_EN field value */
enum ipa_cs_offload_en {
	IPA_CS_OFFLOAD_NONE			= 0x0,
	IPA_CS_OFFLOAD_UL	/* TX */	= 0x1,	/* Not IPA v4.5+ */
	IPA_CS_OFFLOAD_DL	/* RX */	= 0x2,	/* Not IPA v4.5+ */
	IPA_CS_OFFLOAD_INLINE	/* TX and RX */	= 0x1,	/* IPA v4.5+ */
};
=======
/* Not all of the following are present (depends on IPA version) */
#define IPA_REG_SRC_RSRC_GRP_01_RSRC_TYPE_N_OFFSET(rt) \
					(0x00000400 + 0x0020 * (rt))
#define IPA_REG_SRC_RSRC_GRP_23_RSRC_TYPE_N_OFFSET(rt) \
					(0x00000404 + 0x0020 * (rt))
#define IPA_REG_SRC_RSRC_GRP_45_RSRC_TYPE_N_OFFSET(rt) \
					(0x00000408 + 0x0020 * (rt))
#define IPA_REG_SRC_RSRC_GRP_67_RSRC_TYPE_N_OFFSET(rt) \
					(0x0000040c + 0x0020 * (rt))
#define IPA_REG_DST_RSRC_GRP_01_RSRC_TYPE_N_OFFSET(rt) \
					(0x00000500 + 0x0020 * (rt))
#define IPA_REG_DST_RSRC_GRP_23_RSRC_TYPE_N_OFFSET(rt) \
					(0x00000504 + 0x0020 * (rt))
#define IPA_REG_DST_RSRC_GRP_45_RSRC_TYPE_N_OFFSET(rt) \
					(0x00000508 + 0x0020 * (rt))
#define IPA_REG_DST_RSRC_GRP_67_RSRC_TYPE_N_OFFSET(rt) \
					(0x0000050c + 0x0020 * (rt))
/* The next four fields are used for all resource group registers */
#define X_MIN_LIM_FMASK				GENMASK(5, 0)
#define X_MAX_LIM_FMASK				GENMASK(13, 8)
/* The next two fields are not always present (if resource count is odd) */
#define Y_MIN_LIM_FMASK				GENMASK(21, 16)
#define Y_MAX_LIM_FMASK				GENMASK(29, 24)

#define IPA_REG_ENDP_INIT_CTRL_N_OFFSET(ep) \
					(0x00000800 + 0x0070 * (ep))
/* Valid only for RX (IPA producer) endpoints (do not use for IPA v4.0+) */
#define ENDP_SUSPEND_FMASK			GENMASK(0, 0)
/* Valid only for TX (IPA consumer) endpoints */
#define ENDP_DELAY_FMASK			GENMASK(1, 1)

#define IPA_REG_ENDP_INIT_CFG_N_OFFSET(ep) \
					(0x00000808 + 0x0070 * (ep))
#define FRAG_OFFLOAD_EN_FMASK			GENMASK(0, 0)
#define CS_OFFLOAD_EN_FMASK			GENMASK(2, 1)
#define CS_METADATA_HDR_OFFSET_FMASK		GENMASK(6, 3)
#define CS_GEN_QMB_MASTER_SEL_FMASK		GENMASK(8, 8)

/** enum ipa_cs_offload_en - ENDP_INIT_CFG register CS_OFFLOAD_EN field value */
enum ipa_cs_offload_en {
	IPA_CS_OFFLOAD_NONE		= 0x0,
	IPA_CS_OFFLOAD_UL		= 0x1,	/* Before IPA v4.5 (TX) */
	IPA_CS_OFFLOAD_DL		= 0x2,	/* Before IPA v4.5 (RX) */
	IPA_CS_OFFLOAD_INLINE		= 0x1,	/* IPA v4.5 (TX and RX) */
};

/* Valid only for TX (IPA consumer) endpoints */
#define IPA_REG_ENDP_INIT_NAT_N_OFFSET(ep) \
					(0x0000080c + 0x0070 * (ep))
#define NAT_EN_FMASK				GENMASK(1, 0)

/** enum ipa_nat_en - ENDP_INIT_NAT register NAT_EN field value */
enum ipa_nat_en {
	IPA_NAT_BYPASS			= 0x0,
	IPA_NAT_SRC			= 0x1,
	IPA_NAT_DST			= 0x2,
};

#define IPA_REG_ENDP_INIT_HDR_N_OFFSET(ep) \
					(0x00000810 + 0x0070 * (ep))
#define HDR_LEN_FMASK				GENMASK(5, 0)
#define HDR_OFST_METADATA_VALID_FMASK		GENMASK(6, 6)
#define HDR_OFST_METADATA_FMASK			GENMASK(12, 7)
#define HDR_ADDITIONAL_CONST_LEN_FMASK		GENMASK(18, 13)
#define HDR_OFST_PKT_SIZE_VALID_FMASK		GENMASK(19, 19)
#define HDR_OFST_PKT_SIZE_FMASK			GENMASK(25, 20)
/* The next field is not present for IPA v4.9+ */
#define HDR_A5_MUX_FMASK			GENMASK(26, 26)
#define HDR_LEN_INC_DEAGG_HDR_FMASK		GENMASK(27, 27)
/* The next field is not present for IPA v4.5+ */
#define HDR_METADATA_REG_VALID_FMASK		GENMASK(28, 28)
/* The next two fields are present for IPA v4.5+ */
#define HDR_LEN_MSB_FMASK			GENMASK(29, 28)
#define HDR_OFST_METADATA_MSB_FMASK		GENMASK(31, 30)

/* Encoded value for ENDP_INIT_HDR register HDR_LEN* field(s) */
static inline u32 ipa_header_size_encoded(enum ipa_version version,
					  u32 header_size)
{
	u32 size = header_size & field_mask(HDR_LEN_FMASK);
	u32 val;

	val = u32_encode_bits(size, HDR_LEN_FMASK);
	if (version < IPA_VERSION_4_5) {
		WARN_ON(header_size != size);
		return val;
	}

	/* IPA v4.5 adds a few more most-significant bits */
	size = header_size >> hweight32(HDR_LEN_FMASK);
	val |= u32_encode_bits(size, HDR_LEN_MSB_FMASK);
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2

/* ENDP_INIT_NAT register */
enum ipa_reg_endp_init_nat_field_id {
	NAT_EN,
};

/** enum ipa_nat_en - ENDP_INIT_NAT register NAT_EN field value */
enum ipa_nat_en {
	IPA_NAT_BYPASS				= 0x0,
	IPA_NAT_SRC				= 0x1,
	IPA_NAT_DST				= 0x2,
};

<<<<<<< HEAD
/* ENDP_INIT_HDR register */
enum ipa_reg_endp_init_hdr_field_id {
	HDR_LEN,
	HDR_OFST_METADATA_VALID,
	HDR_OFST_METADATA,
	HDR_ADDITIONAL_CONST_LEN,
	HDR_OFST_PKT_SIZE_VALID,
	HDR_OFST_PKT_SIZE,
	HDR_A5_MUX,					/* Not v4.9+ */
	HDR_LEN_INC_DEAGG_HDR,
	HDR_METADATA_REG_VALID,				/* Not v4.5+ */
	HDR_LEN_MSB,					/* v4.5+ */
	HDR_OFST_METADATA_MSB,				/* v4.5+ */
};
=======
	val = u32_encode_bits(off, HDR_OFST_METADATA_FMASK);
	if (version < IPA_VERSION_4_5) {
		WARN_ON(offset != off);
		return val;
	}
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2

/* ENDP_INIT_HDR_EXT register */
enum ipa_reg_endp_init_hdr_ext_field_id {
	HDR_ENDIANNESS,
	HDR_TOTAL_LEN_OR_PAD_VALID,
	HDR_TOTAL_LEN_OR_PAD,
	HDR_PAYLOAD_LEN_INC_PADDING,
	HDR_TOTAL_LEN_OR_PAD_OFFSET,
	HDR_PAD_TO_ALIGNMENT,
	HDR_TOTAL_LEN_OR_PAD_OFFSET_MSB,		/* v4.5+ */
	HDR_OFST_PKT_SIZE_MSB,				/* v4.5+ */
	HDR_ADDITIONAL_CONST_LEN_MSB,			/* v4.5+ */
};

/* ENDP_INIT_MODE register */
enum ipa_reg_endp_init_mode_field_id {
	ENDP_MODE,
	DCPH_ENABLE,					/* v4.5+ */
	DEST_PIPE_INDEX,
	BYTE_THRESHOLD,
	PIPE_REPLICATION_EN,
	PAD_EN,
	HDR_FTCH_DISABLE,				/* v4.5+ */
	DRBIP_ACL_ENABLE,				/* v4.9+ */
};

<<<<<<< HEAD
=======
#define IPA_REG_ENDP_INIT_HDR_EXT_N_OFFSET(ep) \
					(0x00000814 + 0x0070 * (ep))
#define HDR_ENDIANNESS_FMASK			GENMASK(0, 0)
#define HDR_TOTAL_LEN_OR_PAD_VALID_FMASK	GENMASK(1, 1)
#define HDR_TOTAL_LEN_OR_PAD_FMASK		GENMASK(2, 2)
#define HDR_PAYLOAD_LEN_INC_PADDING_FMASK	GENMASK(3, 3)
#define HDR_TOTAL_LEN_OR_PAD_OFFSET_FMASK	GENMASK(9, 4)
#define HDR_PAD_TO_ALIGNMENT_FMASK		GENMASK(13, 10)
/* The next three fields are present for IPA v4.5+ */
#define HDR_TOTAL_LEN_OR_PAD_OFFSET_MSB_FMASK	GENMASK(17, 16)
#define HDR_OFST_PKT_SIZE_MSB_FMASK		GENMASK(19, 18)
#define HDR_ADDITIONAL_CONST_LEN_MSB_FMASK	GENMASK(21, 20)

/* Valid only for RX (IPA producer) endpoints */
#define IPA_REG_ENDP_INIT_HDR_METADATA_MASK_N_OFFSET(rxep) \
					(0x00000818 + 0x0070 * (rxep))

/* Valid only for TX (IPA consumer) endpoints */
#define IPA_REG_ENDP_INIT_MODE_N_OFFSET(txep) \
					(0x00000820 + 0x0070 * (txep))
#define MODE_FMASK				GENMASK(2, 0)
/* The next field is present for IPA v4.5+ */
#define DCPH_ENABLE_FMASK			GENMASK(3, 3)
#define DEST_PIPE_INDEX_FMASK			GENMASK(8, 4)
#define BYTE_THRESHOLD_FMASK			GENMASK(27, 12)
#define PIPE_REPLICATION_EN_FMASK		GENMASK(28, 28)
#define PAD_EN_FMASK				GENMASK(29, 29)
/* The next field is not present for IPA v4.5+ */
#define HDR_FTCH_DISABLE_FMASK			GENMASK(30, 30)
/* The next field is present for IPA v4.9+ */
#define DRBIP_ACL_ENABLE			GENMASK(30, 30)

>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
/** enum ipa_mode - ENDP_INIT_MODE register MODE field value */
enum ipa_mode {
	IPA_BASIC				= 0x0,
	IPA_ENABLE_FRAMING_HDLC			= 0x1,
	IPA_ENABLE_DEFRAMING_HDLC		= 0x2,
	IPA_DMA					= 0x3,
};

<<<<<<< HEAD
/* ENDP_INIT_AGGR register */
enum ipa_reg_endp_init_aggr_field_id {
	AGGR_EN,
	AGGR_TYPE,
	BYTE_LIMIT,
	TIME_LIMIT,
	PKT_LIMIT,
	SW_EOF_ACTIVE,
	FORCE_CLOSE,
	HARD_BYTE_LIMIT_EN,
	AGGR_GRAN_SEL,
};

/** enum ipa_aggr_en - ENDP_INIT_AGGR register AGGR_EN field value */
enum ipa_aggr_en {
	IPA_BYPASS_AGGR		/* TX and RX */	= 0x0,
	IPA_ENABLE_AGGR		/* RX */	= 0x1,
	IPA_ENABLE_DEAGGR	/* TX */	= 0x2,
};

/** enum ipa_aggr_type - ENDP_INIT_AGGR register AGGR_TYPE field value */
enum ipa_aggr_type {
	IPA_MBIM_16				= 0x0,
	IPA_HDLC				= 0x1,
	IPA_TLP					= 0x2,
	IPA_RNDIS				= 0x3,
	IPA_GENERIC				= 0x4,
	IPA_COALESCE				= 0x5,
	IPA_QCMAP				= 0x6,
};

/* ENDP_INIT_HOL_BLOCK_EN register */
enum ipa_reg_endp_init_hol_block_en_field_id {
	HOL_BLOCK_EN,
};

/* ENDP_INIT_HOL_BLOCK_TIMER register */
enum ipa_reg_endp_init_hol_block_timer_field_id {
	TIMER_BASE_VALUE,				/* Not v4.5+ */
	TIMER_SCALE,					/* v4.2 only */
	TIMER_LIMIT,					/* v4.5+ */
	TIMER_GRAN_SEL,					/* v4.5+ */
};

/* ENDP_INIT_DEAGGR register */
enum ipa_reg_endp_deaggr_field_id {
	DEAGGR_HDR_LEN,
	SYSPIPE_ERR_DETECTION,
	PACKET_OFFSET_VALID,
	PACKET_OFFSET_LOCATION,
	IGNORE_MIN_PKT_ERR,
	MAX_PACKET_LEN,
};

/* ENDP_INIT_RSRC_GRP register */
enum ipa_reg_endp_init_rsrc_grp_field_id {
	ENDP_RSRC_GRP,
};

/* ENDP_INIT_SEQ register */
enum ipa_reg_endp_init_seq_field_id {
	SEQ_TYPE,
	SEQ_REP_TYPE,					/* Not v4.5+ */
};
=======
#define IPA_REG_ENDP_INIT_AGGR_N_OFFSET(ep) \
					(0x00000824 +  0x0070 * (ep))
#define AGGR_EN_FMASK				GENMASK(1, 0)
#define AGGR_TYPE_FMASK				GENMASK(4, 2)

/* The legacy value is used for IPA hardware before IPA v4.5 */
static inline u32 aggr_byte_limit_fmask(bool legacy)
{
	return legacy ? GENMASK(9, 5) : GENMASK(10, 5);
}

/* The legacy value is used for IPA hardware before IPA v4.5 */
static inline u32 aggr_time_limit_fmask(bool legacy)
{
	return legacy ? GENMASK(14, 10) : GENMASK(16, 12);
}

/* The legacy value is used for IPA hardware before IPA v4.5 */
static inline u32 aggr_pkt_limit_fmask(bool legacy)
{
	return legacy ? GENMASK(20, 15) : GENMASK(22, 17);
}

/* The legacy value is used for IPA hardware before IPA v4.5 */
static inline u32 aggr_sw_eof_active_fmask(bool legacy)
{
	return legacy ? GENMASK(21, 21) : GENMASK(23, 23);
}

/* The legacy value is used for IPA hardware before IPA v4.5 */
static inline u32 aggr_force_close_fmask(bool legacy)
{
	return legacy ? GENMASK(22, 22) : GENMASK(24, 24);
}

/* The legacy value is used for IPA hardware before IPA v4.5 */
static inline u32 aggr_hard_byte_limit_enable_fmask(bool legacy)
{
	return legacy ? GENMASK(24, 24) : GENMASK(26, 26);
}

/* The next field is present for IPA v4.5+ */
#define AGGR_GRAN_SEL_FMASK			GENMASK(27, 27)

/** enum ipa_aggr_en - ENDP_INIT_AGGR register AGGR_EN field value */
enum ipa_aggr_en {
	IPA_BYPASS_AGGR			= 0x0,	/* (TX, RX) */
	IPA_ENABLE_AGGR			= 0x1,	/* (RX) */
	IPA_ENABLE_DEAGGR		= 0x2,	/* (TX) */
};

/** enum ipa_aggr_type - ENDP_INIT_AGGR register AGGR_TYPE field value */
enum ipa_aggr_type {
	IPA_MBIM_16			= 0x0,
	IPA_HDLC			= 0x1,
	IPA_TLP				= 0x2,
	IPA_RNDIS			= 0x3,
	IPA_GENERIC			= 0x4,
	IPA_COALESCE			= 0x5,
	IPA_QCMAP			= 0x6,
};

/* Valid only for RX (IPA producer) endpoints */
#define IPA_REG_ENDP_INIT_HOL_BLOCK_EN_N_OFFSET(rxep) \
					(0x0000082c +  0x0070 * (rxep))
#define HOL_BLOCK_EN_FMASK			GENMASK(0, 0)

/* Valid only for RX (IPA producer) endpoints */
#define IPA_REG_ENDP_INIT_HOL_BLOCK_TIMER_N_OFFSET(rxep) \
					(0x00000830 +  0x0070 * (rxep))
/* The next two fields are present for IPA v4.2 only */
#define BASE_VALUE_FMASK			GENMASK(4, 0)
#define SCALE_FMASK				GENMASK(12, 8)
/* The next two fields are present for IPA v4.5 */
#define TIME_LIMIT_FMASK			GENMASK(4, 0)
#define GRAN_SEL_FMASK				GENMASK(8, 8)

/* Valid only for TX (IPA consumer) endpoints */
#define IPA_REG_ENDP_INIT_DEAGGR_N_OFFSET(txep) \
					(0x00000834 + 0x0070 * (txep))
#define DEAGGR_HDR_LEN_FMASK			GENMASK(5, 0)
#define SYSPIPE_ERR_DETECTION_FMASK		GENMASK(6, 6)
#define PACKET_OFFSET_VALID_FMASK		GENMASK(7, 7)
#define PACKET_OFFSET_LOCATION_FMASK		GENMASK(13, 8)
#define IGNORE_MIN_PKT_ERR_FMASK		GENMASK(14, 14)
#define MAX_PACKET_LEN_FMASK			GENMASK(31, 16)

#define IPA_REG_ENDP_INIT_RSRC_GRP_N_OFFSET(ep) \
					(0x00000838 + 0x0070 * (ep))
/* Encoded value for ENDP_INIT_RSRC_GRP register RSRC_GRP field */
static inline u32 rsrc_grp_encoded(enum ipa_version version, u32 rsrc_grp)
{
	if (version < IPA_VERSION_3_5 || version == IPA_VERSION_4_5)
		return u32_encode_bits(rsrc_grp, GENMASK(2, 0));

	if (version == IPA_VERSION_4_2 || version == IPA_VERSION_4_7)
		return u32_encode_bits(rsrc_grp, GENMASK(0, 0));

	return u32_encode_bits(rsrc_grp, GENMASK(1, 0));
}

/* Valid only for TX (IPA consumer) endpoints */
#define IPA_REG_ENDP_INIT_SEQ_N_OFFSET(txep) \
					(0x0000083c + 0x0070 * (txep))
#define SEQ_TYPE_FMASK				GENMASK(7, 0)
#define SEQ_REP_TYPE_FMASK			GENMASK(15, 8)
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2

/**
 * enum ipa_seq_type - HPS and DPS sequencer type
 * @IPA_SEQ_DMA:		 Perform DMA only
 * @IPA_SEQ_1_PASS:		 One pass through the pipeline
 * @IPA_SEQ_2_PASS_SKIP_LAST_UC: Two passes, skip the microcprocessor
 * @IPA_SEQ_1_PASS_SKIP_LAST_UC: One pass, skip the microcprocessor
 * @IPA_SEQ_2_PASS:		 Two passes through the pipeline
 * @IPA_SEQ_3_PASS_SKIP_LAST_UC: Three passes, skip the microcprocessor
 * @IPA_SEQ_DECIPHER:		 Optional deciphering step (combined)
 *
 * The low-order byte of the sequencer type register defines the number of
 * passes a packet takes through the IPA pipeline.  The last pass through can
 * optionally skip the microprocessor.  Deciphering is optional for all types;
 * if enabled, an additional mask (two bits) is added to the type value.
 *
 * Note: not all combinations of ipa_seq_type and ipa_seq_rep_type are
 * supported (or meaningful).
 */
enum ipa_seq_type {
	IPA_SEQ_DMA				= 0x00,
	IPA_SEQ_1_PASS				= 0x02,
	IPA_SEQ_2_PASS_SKIP_LAST_UC		= 0x04,
	IPA_SEQ_1_PASS_SKIP_LAST_UC		= 0x06,
	IPA_SEQ_2_PASS				= 0x0a,
	IPA_SEQ_3_PASS_SKIP_LAST_UC		= 0x0c,
	/* The next value can be ORed with the above */
	IPA_SEQ_DECIPHER			= 0x11,
};

/**
 * enum ipa_seq_rep_type - replicated packet sequencer type
 * @IPA_SEQ_REP_DMA_PARSER:	DMA parser for replicated packets
 *
 * This goes in the second byte of the endpoint sequencer type register.
 *
 * Note: not all combinations of ipa_seq_type and ipa_seq_rep_type are
 * supported (or meaningful).
 */
enum ipa_seq_rep_type {
	IPA_SEQ_REP_DMA_PARSER			= 0x08,
};

<<<<<<< HEAD
/* ENDP_STATUS register */
enum ipa_reg_endp_status_field_id {
	STATUS_EN,
	STATUS_ENDP,
	STATUS_LOCATION,				/* Not v4.5+ */
	STATUS_PKT_SUPPRESS,				/* v4.0+ */
};

/* ENDP_FILTER_ROUTER_HSH_CFG register */
enum ipa_reg_endp_filter_router_hsh_cfg_field_id {
	FILTER_HASH_MSK_SRC_ID,
	FILTER_HASH_MSK_SRC_IP,
	FILTER_HASH_MSK_DST_IP,
	FILTER_HASH_MSK_SRC_PORT,
	FILTER_HASH_MSK_DST_PORT,
	FILTER_HASH_MSK_PROTOCOL,
	FILTER_HASH_MSK_METADATA,
	FILTER_HASH_MSK_ALL,		/* Bitwise OR of the above 6 fields */

	ROUTER_HASH_MSK_SRC_ID,
	ROUTER_HASH_MSK_SRC_IP,
	ROUTER_HASH_MSK_DST_IP,
	ROUTER_HASH_MSK_SRC_PORT,
	ROUTER_HASH_MSK_DST_PORT,
	ROUTER_HASH_MSK_PROTOCOL,
	ROUTER_HASH_MSK_METADATA,
	ROUTER_HASH_MSK_ALL,		/* Bitwise OR of the above 6 fields */
};

/* IPA_IRQ_STTS, IPA_IRQ_EN, and IPA_IRQ_CLR registers */
=======
#define IPA_REG_ENDP_STATUS_N_OFFSET(ep) \
					(0x00000840 + 0x0070 * (ep))
#define STATUS_EN_FMASK				GENMASK(0, 0)
#define STATUS_ENDP_FMASK			GENMASK(5, 1)
/* The next field is not present for IPA v4.5+ */
#define STATUS_LOCATION_FMASK			GENMASK(8, 8)
/* The next field is present for IPA v4.0+ */
#define STATUS_PKT_SUPPRESS_FMASK		GENMASK(9, 9)

/* The next register is not present for IPA v4.2 (which no hashing support) */
#define IPA_REG_ENDP_FILTER_ROUTER_HSH_CFG_N_OFFSET(er) \
					(0x0000085c + 0x0070 * (er))
#define FILTER_HASH_MSK_SRC_ID_FMASK		GENMASK(0, 0)
#define FILTER_HASH_MSK_SRC_IP_FMASK		GENMASK(1, 1)
#define FILTER_HASH_MSK_DST_IP_FMASK		GENMASK(2, 2)
#define FILTER_HASH_MSK_SRC_PORT_FMASK		GENMASK(3, 3)
#define FILTER_HASH_MSK_DST_PORT_FMASK		GENMASK(4, 4)
#define FILTER_HASH_MSK_PROTOCOL_FMASK		GENMASK(5, 5)
#define FILTER_HASH_MSK_METADATA_FMASK		GENMASK(6, 6)
#define IPA_REG_ENDP_FILTER_HASH_MSK_ALL	GENMASK(6, 0)

#define ROUTER_HASH_MSK_SRC_ID_FMASK		GENMASK(16, 16)
#define ROUTER_HASH_MSK_SRC_IP_FMASK		GENMASK(17, 17)
#define ROUTER_HASH_MSK_DST_IP_FMASK		GENMASK(18, 18)
#define ROUTER_HASH_MSK_SRC_PORT_FMASK		GENMASK(19, 19)
#define ROUTER_HASH_MSK_DST_PORT_FMASK		GENMASK(20, 20)
#define ROUTER_HASH_MSK_PROTOCOL_FMASK		GENMASK(21, 21)
#define ROUTER_HASH_MSK_METADATA_FMASK		GENMASK(22, 22)
#define IPA_REG_ENDP_ROUTER_HASH_MSK_ALL	GENMASK(22, 16)

static inline u32 ipa_reg_irq_stts_ee_n_offset(enum ipa_version version,
					       u32 ee)
{
	if (version < IPA_VERSION_4_9)
		return 0x00003008 + 0x1000 * ee;

	return 0x00004008 + 0x1000 * ee;
}

static inline u32 ipa_reg_irq_stts_offset(enum ipa_version version)
{
	return ipa_reg_irq_stts_ee_n_offset(version, GSI_EE_AP);
}

static inline u32 ipa_reg_irq_en_ee_n_offset(enum ipa_version version, u32 ee)
{
	if (version < IPA_VERSION_4_9)
		return 0x0000300c + 0x1000 * ee;

	return 0x0000400c + 0x1000 * ee;
}

static inline u32 ipa_reg_irq_en_offset(enum ipa_version version)
{
	return ipa_reg_irq_en_ee_n_offset(version, GSI_EE_AP);
}

static inline u32 ipa_reg_irq_clr_ee_n_offset(enum ipa_version version, u32 ee)
{
	if (version < IPA_VERSION_4_9)
		return 0x00003010 + 0x1000 * ee;

	return 0x00004010 + 0x1000 * ee;
}

static inline u32 ipa_reg_irq_clr_offset(enum ipa_version version)
{
	return ipa_reg_irq_clr_ee_n_offset(version, GSI_EE_AP);
}

>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
/**
 * enum ipa_irq_id - Bit positions representing type of IPA IRQ
 * @IPA_IRQ_UC_0:	Microcontroller event interrupt
 * @IPA_IRQ_UC_1:	Microcontroller response interrupt
 * @IPA_IRQ_TX_SUSPEND:	Data ready interrupt
 * @IPA_IRQ_COUNT:	Number of IRQ ids (must be last)
 *
 * IRQ types not described above are not currently used.
 *
 * @IPA_IRQ_BAD_SNOC_ACCESS:		(Not currently used)
 * @IPA_IRQ_EOT_COAL:			(Not currently used)
 * @IPA_IRQ_UC_2:			(Not currently used)
 * @IPA_IRQ_UC_3:			(Not currently used)
 * @IPA_IRQ_UC_IN_Q_NOT_EMPTY:		(Not currently used)
 * @IPA_IRQ_UC_RX_CMD_Q_NOT_FULL:	(Not currently used)
 * @IPA_IRQ_PROC_UC_ACK_Q_NOT_EMPTY:	(Not currently used)
 * @IPA_IRQ_RX_ERR:			(Not currently used)
 * @IPA_IRQ_DEAGGR_ERR:			(Not currently used)
 * @IPA_IRQ_TX_ERR:			(Not currently used)
 * @IPA_IRQ_STEP_MODE:			(Not currently used)
 * @IPA_IRQ_PROC_ERR:			(Not currently used)
 * @IPA_IRQ_TX_HOLB_DROP:		(Not currently used)
 * @IPA_IRQ_BAM_GSI_IDLE:		(Not currently used)
 * @IPA_IRQ_PIPE_YELLOW_BELOW:		(Not currently used)
 * @IPA_IRQ_PIPE_RED_BELOW:		(Not currently used)
 * @IPA_IRQ_PIPE_YELLOW_ABOVE:		(Not currently used)
 * @IPA_IRQ_PIPE_RED_ABOVE:		(Not currently used)
 * @IPA_IRQ_UCP:			(Not currently used)
 * @IPA_IRQ_DCMP:			(Not currently used)
 * @IPA_IRQ_GSI_EE:			(Not currently used)
 * @IPA_IRQ_GSI_IPA_IF_TLV_RCVD:	(Not currently used)
 * @IPA_IRQ_GSI_UC:			(Not currently used)
 * @IPA_IRQ_TLV_LEN_MIN_DSM:		(Not currently used)
 * @IPA_IRQ_DRBIP_PKT_EXCEED_MAX_SIZE_EN: (Not currently used)
 * @IPA_IRQ_DRBIP_DATA_SCTR_CFG_ERROR_EN: (Not currently used)
 * @IPA_IRQ_DRBIP_IMM_CMD_NO_FLSH_HZRD_EN: (Not currently used)
 */
enum ipa_irq_id {
	IPA_IRQ_BAD_SNOC_ACCESS			= 0x0,
	/* The next bit is not present for IPA v3.5+ */
	IPA_IRQ_EOT_COAL			= 0x1,
	IPA_IRQ_UC_0				= 0x2,
	IPA_IRQ_UC_1				= 0x3,
	IPA_IRQ_UC_2				= 0x4,
	IPA_IRQ_UC_3				= 0x5,
	IPA_IRQ_UC_IN_Q_NOT_EMPTY		= 0x6,
	IPA_IRQ_UC_RX_CMD_Q_NOT_FULL		= 0x7,
	IPA_IRQ_PROC_UC_ACK_Q_NOT_EMPTY		= 0x8,
	IPA_IRQ_RX_ERR				= 0x9,
	IPA_IRQ_DEAGGR_ERR			= 0xa,
	IPA_IRQ_TX_ERR				= 0xb,
	IPA_IRQ_STEP_MODE			= 0xc,
	IPA_IRQ_PROC_ERR			= 0xd,
	IPA_IRQ_TX_SUSPEND			= 0xe,
	IPA_IRQ_TX_HOLB_DROP			= 0xf,
	IPA_IRQ_BAM_GSI_IDLE			= 0x10,
	IPA_IRQ_PIPE_YELLOW_BELOW		= 0x11,
	IPA_IRQ_PIPE_RED_BELOW			= 0x12,
	IPA_IRQ_PIPE_YELLOW_ABOVE		= 0x13,
	IPA_IRQ_PIPE_RED_ABOVE			= 0x14,
	IPA_IRQ_UCP				= 0x15,
	/* The next bit is not present for IPA v4.5+ */
	IPA_IRQ_DCMP				= 0x16,
	IPA_IRQ_GSI_EE				= 0x17,
	IPA_IRQ_GSI_IPA_IF_TLV_RCVD		= 0x18,
	IPA_IRQ_GSI_UC				= 0x19,
	/* The next bit is present for IPA v4.5+ */
	IPA_IRQ_TLV_LEN_MIN_DSM			= 0x1a,
	/* The next three bits are present for IPA v4.9+ */
	IPA_IRQ_DRBIP_PKT_EXCEED_MAX_SIZE_EN	= 0x1b,
	IPA_IRQ_DRBIP_DATA_SCTR_CFG_ERROR_EN	= 0x1c,
	IPA_IRQ_DRBIP_IMM_CMD_NO_FLSH_HZRD_EN	= 0x1d,
	IPA_IRQ_COUNT,				/* Last; not an id */
};

<<<<<<< HEAD
/* IPA_IRQ_UC register */
enum ipa_reg_ipa_irq_uc_field_id {
	UC_INTR,
};

extern const struct ipa_regs ipa_regs_v3_1;
extern const struct ipa_regs ipa_regs_v3_5_1;
extern const struct ipa_regs ipa_regs_v4_2;
extern const struct ipa_regs ipa_regs_v4_5;
extern const struct ipa_regs ipa_regs_v4_9;
extern const struct ipa_regs ipa_regs_v4_11;

/* Return the field mask for a field in a register */
static inline u32 ipa_reg_fmask(const struct ipa_reg *reg, u32 field_id)
{
	if (!reg || WARN_ON(field_id >= reg->fcount))
		return 0;

	return reg->fmask[field_id];
}

/* Return the mask for a single-bit field in a register */
static inline u32 ipa_reg_bit(const struct ipa_reg *reg, u32 field_id)
{
	u32 fmask = ipa_reg_fmask(reg, field_id);

	WARN_ON(!is_power_of_2(fmask));

	return fmask;
}

/* Encode a value into the given field of a register */
static inline u32
ipa_reg_encode(const struct ipa_reg *reg, u32 field_id, u32 val)
{
	u32 fmask = ipa_reg_fmask(reg, field_id);

	if (!fmask)
		return 0;

	val <<= __ffs(fmask);
	if (WARN_ON(val & ~fmask))
		return 0;

	return val;
}

/* Given a register value, decode (extract) the value in the given field */
static inline u32
ipa_reg_decode(const struct ipa_reg *reg, u32 field_id, u32 val)
{
	u32 fmask = ipa_reg_fmask(reg, field_id);

	return fmask ? (val & fmask) >> __ffs(fmask) : 0;
}

/* Return the maximum value representable by the given field; always 2^n - 1 */
static inline u32 ipa_reg_field_max(const struct ipa_reg *reg, u32 field_id)
{
	u32 fmask = ipa_reg_fmask(reg, field_id);

	return fmask ? fmask >> __ffs(fmask) : 0;
}

const struct ipa_reg *ipa_reg(struct ipa *ipa, enum ipa_reg_id reg_id);

/* Returns 0 for NULL reg; warning will have already been issued */
static inline u32 ipa_reg_offset(const struct ipa_reg *reg)
{
	return reg ? reg->offset : 0;
}

/* Returns 0 for NULL reg; warning will have already been issued */
static inline u32 ipa_reg_n_offset(const struct ipa_reg *reg, u32 n)
{
	return reg ? reg->offset + n * reg->stride : 0;
=======
static inline u32 ipa_reg_irq_uc_ee_n_offset(enum ipa_version version, u32 ee)
{
	if (version < IPA_VERSION_4_9)
		return 0x0000301c + 0x1000 * ee;

	return 0x0000401c + 0x1000 * ee;
}

static inline u32 ipa_reg_irq_uc_offset(enum ipa_version version)
{
	return ipa_reg_irq_uc_ee_n_offset(version, GSI_EE_AP);
}

#define UC_INTR_FMASK				GENMASK(0, 0)

/* ipa->available defines the valid bits in the SUSPEND_INFO register */
static inline u32
ipa_reg_irq_suspend_info_ee_n_offset(enum ipa_version version, u32 ee)
{
	if (version == IPA_VERSION_3_0)
		return 0x00003098 + 0x1000 * ee;

	if (version < IPA_VERSION_4_9)
		return 0x00003030 + 0x1000 * ee;

	return 0x00004030 + 0x1000 * ee;
}

static inline u32
ipa_reg_irq_suspend_info_offset(enum ipa_version version)
{
	return ipa_reg_irq_suspend_info_ee_n_offset(version, GSI_EE_AP);
}

/* ipa->available defines the valid bits in the SUSPEND_EN register */
static inline u32
ipa_reg_irq_suspend_en_ee_n_offset(enum ipa_version version, u32 ee)
{
	WARN_ON(version == IPA_VERSION_3_0);

	if (version < IPA_VERSION_4_9)
		return 0x00003034 + 0x1000 * ee;

	return 0x00004034 + 0x1000 * ee;
}

static inline u32
ipa_reg_irq_suspend_en_offset(enum ipa_version version)
{
	return ipa_reg_irq_suspend_en_ee_n_offset(version, GSI_EE_AP);
}

/* ipa->available defines the valid bits in the SUSPEND_CLR register */
static inline u32
ipa_reg_irq_suspend_clr_ee_n_offset(enum ipa_version version, u32 ee)
{
	WARN_ON(version == IPA_VERSION_3_0);

	if (version < IPA_VERSION_4_9)
		return 0x00003038 + 0x1000 * ee;

	return 0x00004038 + 0x1000 * ee;
}

static inline u32
ipa_reg_irq_suspend_clr_offset(enum ipa_version version)
{
	return ipa_reg_irq_suspend_clr_ee_n_offset(version, GSI_EE_AP);
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
}

int ipa_reg_init(struct ipa *ipa);
void ipa_reg_exit(struct ipa *ipa);

#endif /* _IPA_REG_H_ */
