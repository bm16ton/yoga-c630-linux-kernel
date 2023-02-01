/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * DMA-BUF sysfs statistics.
 *
 * Copyright (C) 2021 Google LLC.
 */

#ifndef _DMA_BUF_SYSFS_STATS_H
#define _DMA_BUF_SYSFS_STATS_H

#ifdef CONFIG_DMABUF_SYSFS_STATS

int dma_buf_init_sysfs_statistics(void);
void dma_buf_uninit_sysfs_statistics(void);

<<<<<<< HEAD
int dma_buf_stats_setup(struct dma_buf *dmabuf, struct file *file);
=======
int dma_buf_stats_setup(struct dma_buf *dmabuf);
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2

void dma_buf_stats_teardown(struct dma_buf *dmabuf);
#else

static inline int dma_buf_init_sysfs_statistics(void)
{
	return 0;
}

static inline void dma_buf_uninit_sysfs_statistics(void) {}

<<<<<<< HEAD
static inline int dma_buf_stats_setup(struct dma_buf *dmabuf, struct file *file)
=======
static inline int dma_buf_stats_setup(struct dma_buf *dmabuf)
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
{
	return 0;
}

static inline void dma_buf_stats_teardown(struct dma_buf *dmabuf) {}
#endif
#endif // _DMA_BUF_SYSFS_STATS_H
