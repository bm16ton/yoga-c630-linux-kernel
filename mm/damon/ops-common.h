/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Common Primitives for Data Access Monitoring
 *
 * Author: SeongJae Park <sj@kernel.org>
 */

#include <linux/damon.h>

struct page *damon_get_page(unsigned long pfn);

void damon_ptep_mkold(pte_t *pte, struct mm_struct *mm, unsigned long addr);
void damon_pmdp_mkold(pmd_t *pmd, struct mm_struct *mm, unsigned long addr);

<<<<<<< HEAD
int damon_cold_score(struct damon_ctx *c, struct damon_region *r,
=======
int damon_pageout_score(struct damon_ctx *c, struct damon_region *r,
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
			struct damos *s);
int damon_hot_score(struct damon_ctx *c, struct damon_region *r,
			struct damos *s);
