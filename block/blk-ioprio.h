/* SPDX-License-Identifier: GPL-2.0 */

#ifndef _BLK_IOPRIO_H_
#define _BLK_IOPRIO_H_

#include <linux/kconfig.h>

struct request_queue;
struct bio;

#ifdef CONFIG_BLK_CGROUP_IOPRIO
<<<<<<< HEAD
int blk_ioprio_init(struct gendisk *disk);
void blk_ioprio_exit(struct gendisk *disk);
void blkcg_set_ioprio(struct bio *bio);
#else
static inline int blk_ioprio_init(struct gendisk *disk)
{
	return 0;
}
static inline void blk_ioprio_exit(struct gendisk *disk)
=======
int blk_ioprio_init(struct request_queue *q);
void blk_ioprio_exit(struct request_queue *q);
void blkcg_set_ioprio(struct bio *bio);
#else
static inline int blk_ioprio_init(struct request_queue *q)
{
	return 0;
}
static inline void blk_ioprio_exit(struct request_queue *q)
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
{
}
static inline void blkcg_set_ioprio(struct bio *bio)
{
}
#endif

#endif /* _BLK_IOPRIO_H_ */
