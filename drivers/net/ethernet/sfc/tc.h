/* SPDX-License-Identifier: GPL-2.0-only */
/****************************************************************************
 * Driver for Solarflare network controllers and boards
 * Copyright 2019 Solarflare Communications Inc.
 * Copyright 2020-2022 Xilinx Inc.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation, incorporated herein by reference.
 */

#ifndef EFX_TC_H
#define EFX_TC_H
<<<<<<< HEAD
#include <net/flow_offload.h>
#include <linux/rhashtable.h>
#include "net_driver.h"

/* Error reporting: convenience macros.  For indicating why a given filter
 * insertion is not supported; errors in internal operation or in the
 * hardware should be netif_err()s instead.
 */
/* Used when error message is constant. */
#define EFX_TC_ERR_MSG(efx, extack, message)	do {			\
	NL_SET_ERR_MSG_MOD(extack, message);				\
	if (efx->log_tc_errs)						\
		netif_info(efx, drv, efx->net_dev, "%s\n", message);	\
} while (0)
/* Used when error message is not constant; caller should also supply a
 * constant extack message with NL_SET_ERR_MSG_MOD().
 */
#define efx_tc_err(efx, fmt, args...)	do {		\
if (efx->log_tc_errs)					\
	netif_info(efx, drv, efx->net_dev, fmt, ##args);\
} while (0)

=======
#include "net_driver.h"

>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
struct efx_tc_action_set {
	u16 deliver:1;
	u32 dest_mport;
	u32 fw_id; /* index of this entry in firmware actions table */
	struct list_head list;
};

struct efx_tc_match_fields {
	/* L1 */
	u32 ingress_port;
<<<<<<< HEAD
	u8 recirc_id;
=======
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
};

struct efx_tc_match {
	struct efx_tc_match_fields value;
	struct efx_tc_match_fields mask;
};

struct efx_tc_action_set_list {
	struct list_head list;
	u32 fw_id;
};

struct efx_tc_flow_rule {
<<<<<<< HEAD
	unsigned long cookie;
	struct rhash_head linkage;
=======
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
	struct efx_tc_match match;
	struct efx_tc_action_set_list acts;
	u32 fw_id;
};

enum efx_tc_rule_prios {
<<<<<<< HEAD
	EFX_TC_PRIO_TC, /* Rule inserted by TC */
=======
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
	EFX_TC_PRIO_DFLT, /* Default switch rule; one of efx_tc_default_rules */
	EFX_TC_PRIO__NUM
};

/**
 * struct efx_tc_state - control plane data for TC offload
 *
<<<<<<< HEAD
 * @caps: MAE capabilities reported by MCDI
 * @block_list: List of &struct efx_tc_block_binding
 * @mutex: Used to serialise operations on TC hashtables
 * @match_action_ht: Hashtable of TC match-action rules
=======
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
 * @reps_mport_id: MAE port allocated for representor RX
 * @reps_filter_uc: VNIC filter for representor unicast RX (promisc)
 * @reps_filter_mc: VNIC filter for representor multicast RX (allmulti)
 * @reps_mport_vport_id: vport_id for representor RX filters
 * @dflt: Match-action rules for default switching; at priority
 *	%EFX_TC_PRIO_DFLT.  Named by *ingress* port
 * @dflt.pf: rule for traffic ingressing from PF (egresses to wire)
 * @dflt.wire: rule for traffic ingressing from wire (egresses to PF)
<<<<<<< HEAD
 * @up: have TC datastructures been set up?
 */
struct efx_tc_state {
	struct mae_caps *caps;
	struct list_head block_list;
	struct mutex mutex;
	struct rhashtable match_action_ht;
=======
 */
struct efx_tc_state {
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
	u32 reps_mport_id, reps_mport_vport_id;
	s32 reps_filter_uc, reps_filter_mc;
	struct {
		struct efx_tc_flow_rule pf;
		struct efx_tc_flow_rule wire;
	} dflt;
<<<<<<< HEAD
	bool up;
=======
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
};

struct efx_rep;

int efx_tc_configure_default_rule_rep(struct efx_rep *efv);
void efx_tc_deconfigure_default_rule(struct efx_nic *efx,
				     struct efx_tc_flow_rule *rule);
<<<<<<< HEAD
int efx_tc_flower(struct efx_nic *efx, struct net_device *net_dev,
		  struct flow_cls_offload *tc, struct efx_rep *efv);
=======
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2

int efx_tc_insert_rep_filters(struct efx_nic *efx);
void efx_tc_remove_rep_filters(struct efx_nic *efx);

int efx_init_tc(struct efx_nic *efx);
void efx_fini_tc(struct efx_nic *efx);

int efx_init_struct_tc(struct efx_nic *efx);
void efx_fini_struct_tc(struct efx_nic *efx);

#endif /* EFX_TC_H */
