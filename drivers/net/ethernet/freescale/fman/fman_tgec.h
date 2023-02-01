/* SPDX-License-Identifier: BSD-3-Clause OR GPL-2.0-or-later */
/*
 * Copyright 2008 - 2015 Freescale Semiconductor Inc.
 */

#ifndef __TGEC_H
#define __TGEC_H

#include "fman_mac.h"

<<<<<<< HEAD
struct mac_device;

int tgec_initialization(struct mac_device *mac_dev,
			struct device_node *mac_node,
			struct fman_mac_params *params);
=======
struct fman_mac *tgec_config(struct fman_mac_params *params);
int tgec_set_promiscuous(struct fman_mac *tgec, bool new_val);
int tgec_modify_mac_address(struct fman_mac *tgec, const enet_addr_t *enet_addr);
int tgec_cfg_max_frame_len(struct fman_mac *tgec, u16 new_val);
int tgec_enable(struct fman_mac *tgec, enum comm_mode mode);
int tgec_disable(struct fman_mac *tgec, enum comm_mode mode);
int tgec_init(struct fman_mac *tgec);
int tgec_free(struct fman_mac *tgec);
int tgec_accept_rx_pause_frames(struct fman_mac *tgec, bool en);
int tgec_set_tx_pause_frames(struct fman_mac *tgec, u8 priority,
			     u16 pause_time, u16 thresh_time);
int tgec_set_exception(struct fman_mac *tgec,
		       enum fman_mac_exceptions exception, bool enable);
int tgec_add_hash_mac_address(struct fman_mac *tgec, enet_addr_t *eth_addr);
int tgec_del_hash_mac_address(struct fman_mac *tgec, enet_addr_t *eth_addr);
int tgec_get_version(struct fman_mac *tgec, u32 *mac_version);
int tgec_set_allmulti(struct fman_mac *tgec, bool enable);
int tgec_set_tstamp(struct fman_mac *tgec, bool enable);
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2

#endif /* __TGEC_H */
