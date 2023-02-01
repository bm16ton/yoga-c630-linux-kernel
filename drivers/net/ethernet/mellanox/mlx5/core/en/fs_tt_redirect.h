/* SPDX-License-Identifier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2021 Mellanox Technologies. */

#ifndef __MLX5E_FS_TT_REDIRECT_H__
#define __MLX5E_FS_TT_REDIRECT_H__

<<<<<<< HEAD
=======
#include "en.h"
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
#include "en/fs.h"

void mlx5e_fs_tt_redirect_del_rule(struct mlx5_flow_handle *rule);

/* UDP traffic type redirect */
struct mlx5_flow_handle *
<<<<<<< HEAD
mlx5e_fs_tt_redirect_udp_add_rule(struct mlx5e_flow_steering *fs,
				  enum mlx5_traffic_types ttc_type,
				  u32 tir_num, u16 d_port);
void mlx5e_fs_tt_redirect_udp_destroy(struct mlx5e_flow_steering *fs);
int mlx5e_fs_tt_redirect_udp_create(struct mlx5e_flow_steering *fs);

/* ANY traffic type redirect*/
struct mlx5_flow_handle *
mlx5e_fs_tt_redirect_any_add_rule(struct mlx5e_flow_steering *fs,
				  u32 tir_num, u16 ether_type);
void mlx5e_fs_tt_redirect_any_destroy(struct mlx5e_flow_steering *fs);
int mlx5e_fs_tt_redirect_any_create(struct mlx5e_flow_steering *fs);
=======
mlx5e_fs_tt_redirect_udp_add_rule(struct mlx5e_priv *priv,
				  enum mlx5_traffic_types ttc_type,
				  u32 tir_num, u16 d_port);
void mlx5e_fs_tt_redirect_udp_destroy(struct mlx5e_priv *priv);
int mlx5e_fs_tt_redirect_udp_create(struct mlx5e_priv *priv);

/* ANY traffic type redirect*/
struct mlx5_flow_handle *
mlx5e_fs_tt_redirect_any_add_rule(struct mlx5e_priv *priv,
				  u32 tir_num, u16 ether_type);
void mlx5e_fs_tt_redirect_any_destroy(struct mlx5e_priv *priv);
int mlx5e_fs_tt_redirect_any_create(struct mlx5e_priv *priv);
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
#endif
