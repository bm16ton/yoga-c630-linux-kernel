// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (C) 2016 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

#include <linux/vmalloc.h>
#include <linux/sched/mm.h>

#include "msm_drv.h"
#include "msm_gem.h"
#include "msm_gpu.h"
#include "msm_gpu_trace.h"

/* Default disabled for now until it has some more testing on the different
 * iommu combinations that can be paired with the driver:
 */
static bool enable_eviction = false;
MODULE_PARM_DESC(enable_eviction, "Enable swappable GEM buffers");
module_param(enable_eviction, bool, 0600);

static bool can_swap(void)
{
	return enable_eviction && get_nr_swap_pages() > 0;
}

<<<<<<< HEAD
static bool can_block(struct shrink_control *sc)
{
	if (!(sc->gfp_mask & __GFP_DIRECT_RECLAIM))
		return false;
	return current_is_kswapd() || (sc->gfp_mask & __GFP_RECLAIM);
}

=======
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
static unsigned long
msm_gem_shrinker_count(struct shrinker *shrinker, struct shrink_control *sc)
{
	struct msm_drm_private *priv =
		container_of(shrinker, struct msm_drm_private, shrinker);
<<<<<<< HEAD
	unsigned count = priv->lru.dontneed.count;

	if (can_swap())
		count += priv->lru.willneed.count;
=======
	unsigned count = priv->shrinkable_count;

	if (can_swap())
		count += priv->evictable_count;
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2

	return count;
}

static bool
<<<<<<< HEAD
purge(struct drm_gem_object *obj)
{
	if (!is_purgeable(to_msm_bo(obj)))
		return false;

	if (msm_gem_active(obj))
		return false;

	msm_gem_purge(obj);
=======
purge(struct msm_gem_object *msm_obj)
{
	if (!is_purgeable(msm_obj))
		return false;

	/*
	 * This will move the obj out of still_in_list to
	 * the purged list
	 */
	msm_gem_purge(&msm_obj->base);
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2

	return true;
}

static bool
<<<<<<< HEAD
evict(struct drm_gem_object *obj)
{
	if (is_unevictable(to_msm_bo(obj)))
		return false;

	if (msm_gem_active(obj))
		return false;

	msm_gem_evict(obj);

	return true;
}

static bool
wait_for_idle(struct drm_gem_object *obj)
{
	enum dma_resv_usage usage = dma_resv_usage_rw(true);
	return dma_resv_wait_timeout(obj->resv, usage, false, 1000) > 0;
}

static bool
active_purge(struct drm_gem_object *obj)
{
	if (!wait_for_idle(obj))
		return false;

	return purge(obj);
}

static bool
active_evict(struct drm_gem_object *obj)
{
	if (!wait_for_idle(obj))
		return false;

	return evict(obj);
=======
evict(struct msm_gem_object *msm_obj)
{
	if (is_unevictable(msm_obj))
		return false;

	msm_gem_evict(&msm_obj->base);

	return true;
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
}

static unsigned long
scan(struct msm_drm_private *priv, unsigned nr_to_scan, struct list_head *list,
		bool (*shrink)(struct msm_gem_object *msm_obj))
{
<<<<<<< HEAD
	struct msm_drm_private *priv =
		container_of(shrinker, struct msm_drm_private, shrinker);
	struct {
		struct drm_gem_lru *lru;
		bool (*shrink)(struct drm_gem_object *obj);
		bool cond;
		unsigned long freed;
	} stages[] = {
		/* Stages of progressively more aggressive/expensive reclaim: */
		{ &priv->lru.dontneed, purge,        true },
		{ &priv->lru.willneed, evict,        can_swap() },
		{ &priv->lru.dontneed, active_purge, can_block(sc) },
		{ &priv->lru.willneed, active_evict, can_swap() && can_block(sc) },
	};
	long nr = sc->nr_to_scan;
	unsigned long freed = 0;

	for (unsigned i = 0; (nr > 0) && (i < ARRAY_SIZE(stages)); i++) {
		if (!stages[i].cond)
			continue;
		stages[i].freed =
			drm_gem_lru_scan(stages[i].lru, nr, stages[i].shrink);
		nr -= stages[i].freed;
		freed += stages[i].freed;
	}

	if (freed) {
		trace_msm_gem_shrink(sc->nr_to_scan, stages[0].freed,
				     stages[1].freed, stages[2].freed,
				     stages[3].freed);
	}

	return (freed > 0) ? freed : SHRINK_STOP;
}

#ifdef CONFIG_DEBUG_FS
unsigned long
msm_gem_shrinker_shrink(struct drm_device *dev, unsigned long nr_to_scan)
{
	struct msm_drm_private *priv = dev->dev_private;
	struct shrink_control sc = {
		.nr_to_scan = nr_to_scan,
	};
	int ret;

	fs_reclaim_acquire(GFP_KERNEL);
	ret = msm_gem_shrinker_scan(&priv->shrinker, &sc);
	fs_reclaim_release(GFP_KERNEL);

	return ret;
=======
	unsigned freed = 0;
	struct list_head still_in_list;

	INIT_LIST_HEAD(&still_in_list);

	mutex_lock(&priv->mm_lock);

	while (freed < nr_to_scan) {
		struct msm_gem_object *msm_obj = list_first_entry_or_null(
				list, typeof(*msm_obj), mm_list);

		if (!msm_obj)
			break;

		list_move_tail(&msm_obj->mm_list, &still_in_list);

		/*
		 * If it is in the process of being freed, msm_gem_free_object
		 * can be blocked on mm_lock waiting to remove it.  So just
		 * skip it.
		 */
		if (!kref_get_unless_zero(&msm_obj->base.refcount))
			continue;

		/*
		 * Now that we own a reference, we can drop mm_lock for the
		 * rest of the loop body, to reduce contention with the
		 * retire_submit path (which could make more objects purgeable)
		 */

		mutex_unlock(&priv->mm_lock);

		/*
		 * Note that this still needs to be trylock, since we can
		 * hit shrinker in response to trying to get backing pages
		 * for this obj (ie. while it's lock is already held)
		 */
		if (!msm_gem_trylock(&msm_obj->base))
			goto tail;

		if (shrink(msm_obj))
			freed += msm_obj->base.size >> PAGE_SHIFT;

		msm_gem_unlock(&msm_obj->base);

tail:
		drm_gem_object_put(&msm_obj->base);
		mutex_lock(&priv->mm_lock);
	}

	list_splice_tail(&still_in_list, list);
	mutex_unlock(&priv->mm_lock);

	return freed;
}

static unsigned long
msm_gem_shrinker_scan(struct shrinker *shrinker, struct shrink_control *sc)
{
	struct msm_drm_private *priv =
		container_of(shrinker, struct msm_drm_private, shrinker);
	unsigned long freed;

	freed = scan(priv, sc->nr_to_scan, &priv->inactive_dontneed, purge);

	if (freed > 0)
		trace_msm_gem_purge(freed << PAGE_SHIFT);

	if (can_swap() && freed < sc->nr_to_scan) {
		int evicted = scan(priv, sc->nr_to_scan - freed,
				&priv->inactive_willneed, evict);

		if (evicted > 0)
			trace_msm_gem_evict(evicted << PAGE_SHIFT);

		freed += evicted;
	}

	return (freed > 0) ? freed : SHRINK_STOP;
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
}
#endif

#ifdef CONFIG_DEBUG_FS
unsigned long
msm_gem_shrinker_shrink(struct drm_device *dev, unsigned long nr_to_scan)
{
	struct msm_drm_private *priv = dev->dev_private;
	struct shrink_control sc = {
		.nr_to_scan = nr_to_scan,
	};
	int ret;

	fs_reclaim_acquire(GFP_KERNEL);
	ret = msm_gem_shrinker_scan(&priv->shrinker, &sc);
	fs_reclaim_release(GFP_KERNEL);

	return ret;
}
#endif

/* since we don't know any better, lets bail after a few
 * and if necessary the shrinker will be invoked again.
 * Seems better than unmapping *everything*
 */
static const int vmap_shrink_limit = 15;

static bool
<<<<<<< HEAD
vmap_shrink(struct drm_gem_object *obj)
{
	if (!is_vunmapable(to_msm_bo(obj)))
		return false;

	msm_gem_vunmap(obj);
=======
vmap_shrink(struct msm_gem_object *msm_obj)
{
	if (!is_vunmapable(msm_obj))
		return false;

	msm_gem_vunmap(&msm_obj->base);
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2

	return true;
}

static int
msm_gem_shrinker_vmap(struct notifier_block *nb, unsigned long event, void *ptr)
{
	struct msm_drm_private *priv =
		container_of(nb, struct msm_drm_private, vmap_notifier);
	struct drm_gem_lru *lrus[] = {
		&priv->lru.dontneed,
		&priv->lru.willneed,
		&priv->lru.pinned,
		NULL,
	};
	unsigned idx, unmapped = 0;

<<<<<<< HEAD
	for (idx = 0; lrus[idx] && unmapped < vmap_shrink_limit; idx++) {
		unmapped += drm_gem_lru_scan(lrus[idx],
					     vmap_shrink_limit - unmapped,
					     vmap_shrink);
=======
	for (idx = 0; mm_lists[idx] && unmapped < vmap_shrink_limit; idx++) {
		unmapped += scan(priv, vmap_shrink_limit - unmapped,
				mm_lists[idx], vmap_shrink);
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
	}

	*(unsigned long *)ptr += unmapped;

	if (unmapped > 0)
		trace_msm_gem_purge_vmaps(unmapped);

	return NOTIFY_DONE;
}

/**
 * msm_gem_shrinker_init - Initialize msm shrinker
 * @dev: drm device
 *
 * This function registers and sets up the msm shrinker.
 */
void msm_gem_shrinker_init(struct drm_device *dev)
{
	struct msm_drm_private *priv = dev->dev_private;
	priv->shrinker.count_objects = msm_gem_shrinker_count;
	priv->shrinker.scan_objects = msm_gem_shrinker_scan;
	priv->shrinker.seeks = DEFAULT_SEEKS;
	WARN_ON(register_shrinker(&priv->shrinker, "drm-msm_gem"));

	priv->vmap_notifier.notifier_call = msm_gem_shrinker_vmap;
	WARN_ON(register_vmap_purge_notifier(&priv->vmap_notifier));
}

/**
 * msm_gem_shrinker_cleanup - Clean up msm shrinker
 * @dev: drm device
 *
 * This function unregisters the msm shrinker.
 */
void msm_gem_shrinker_cleanup(struct drm_device *dev)
{
	struct msm_drm_private *priv = dev->dev_private;

	if (priv->shrinker.nr_deferred) {
		WARN_ON(unregister_vmap_purge_notifier(&priv->vmap_notifier));
		unregister_shrinker(&priv->shrinker);
	}
}
