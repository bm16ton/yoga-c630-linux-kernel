// SPDX-License-Identifier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2021, Mellanox Technologies inc. All rights reserved. */

#include "channels.h"
#include "en.h"
#include "en/ptp.h"

unsigned int mlx5e_channels_get_num(struct mlx5e_channels *chs)
{
	return chs->num;
}

<<<<<<< HEAD
static struct mlx5e_channel *mlx5e_channels_get(struct mlx5e_channels *chs, unsigned int ix)
{
	WARN_ON_ONCE(ix >= mlx5e_channels_get_num(chs));
	return chs->c[ix];
}

bool mlx5e_channels_is_xsk(struct mlx5e_channels *chs, unsigned int ix)
{
	struct mlx5e_channel *c = mlx5e_channels_get(chs, ix);

	return test_bit(MLX5E_CHANNEL_STATE_XSK, c->state);
}

void mlx5e_channels_get_regular_rqn(struct mlx5e_channels *chs, unsigned int ix, u32 *rqn)
{
	struct mlx5e_channel *c = mlx5e_channels_get(chs, ix);
=======
void mlx5e_channels_get_regular_rqn(struct mlx5e_channels *chs, unsigned int ix, u32 *rqn)
{
	struct mlx5e_channel *c;

	WARN_ON(ix >= mlx5e_channels_get_num(chs));
	c = chs->c[ix];
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2

	*rqn = c->rq.rqn;
}

<<<<<<< HEAD
void mlx5e_channels_get_xsk_rqn(struct mlx5e_channels *chs, unsigned int ix, u32 *rqn)
{
	struct mlx5e_channel *c = mlx5e_channels_get(chs, ix);

	WARN_ON_ONCE(!test_bit(MLX5E_CHANNEL_STATE_XSK, c->state));

	*rqn = c->xskrq.rqn;
=======
bool mlx5e_channels_get_xsk_rqn(struct mlx5e_channels *chs, unsigned int ix, u32 *rqn)
{
	struct mlx5e_channel *c;

	WARN_ON(ix >= mlx5e_channels_get_num(chs));
	c = chs->c[ix];

	if (!test_bit(MLX5E_CHANNEL_STATE_XSK, c->state))
		return false;

	*rqn = c->xskrq.rqn;
	return true;
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
}

bool mlx5e_channels_get_ptp_rqn(struct mlx5e_channels *chs, u32 *rqn)
{
	struct mlx5e_ptp *c = chs->ptp;

	if (!c || !test_bit(MLX5E_PTP_STATE_RX, c->state))
		return false;

	*rqn = c->rq.rqn;
	return true;
}
