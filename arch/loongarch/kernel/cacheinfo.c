// SPDX-License-Identifier: GPL-2.0-only
/*
 * LoongArch cacheinfo support
 *
 * Copyright (C) 2020-2022 Loongson Technology Corporation Limited
 */
#include <linux/cacheinfo.h>
<<<<<<< HEAD
#include <linux/topology.h>
#include <asm/bootinfo.h>
#include <asm/cpu-info.h>

int init_cache_level(unsigned int cpu)
{
	int cache_present = current_cpu_data.cache_leaves_present;
	struct cpu_cacheinfo *this_cpu_ci = get_cpu_cacheinfo(cpu);

	this_cpu_ci->num_levels =
		current_cpu_data.cache_leaves[cache_present - 1].level;
	this_cpu_ci->num_leaves = cache_present;

=======
#include <asm/bootinfo.h>
#include <asm/cpu-info.h>

/* Populates leaf and increments to next leaf */
#define populate_cache(cache, leaf, c_level, c_type)		\
do {								\
	leaf->type = c_type;					\
	leaf->level = c_level;					\
	leaf->coherency_line_size = c->cache.linesz;		\
	leaf->number_of_sets = c->cache.sets;			\
	leaf->ways_of_associativity = c->cache.ways;		\
	leaf->size = c->cache.linesz * c->cache.sets *		\
		c->cache.ways;					\
	if (leaf->level > 2)					\
		leaf->size *= nodes_per_package;		\
	leaf++;							\
} while (0)

int init_cache_level(unsigned int cpu)
{
	struct cpuinfo_loongarch *c = &current_cpu_data;
	struct cpu_cacheinfo *this_cpu_ci = get_cpu_cacheinfo(cpu);
	int levels = 0, leaves = 0;

	/*
	 * If Dcache is not set, we assume the cache structures
	 * are not properly initialized.
	 */
	if (c->dcache.waysize)
		levels += 1;
	else
		return -ENOENT;


	leaves += (c->icache.waysize) ? 2 : 1;

	if (c->vcache.waysize) {
		levels++;
		leaves++;
	}

	if (c->scache.waysize) {
		levels++;
		leaves++;
	}

	if (c->tcache.waysize) {
		levels++;
		leaves++;
	}

	this_cpu_ci->num_levels = levels;
	this_cpu_ci->num_leaves = leaves;
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
	return 0;
}

static inline bool cache_leaves_are_shared(struct cacheinfo *this_leaf,
					   struct cacheinfo *sib_leaf)
{
<<<<<<< HEAD
	return (!(*(unsigned char *)(this_leaf->priv) & CACHE_PRIVATE)
		&& !(*(unsigned char *)(sib_leaf->priv) & CACHE_PRIVATE));
=======
	return !((this_leaf->level == 1) || (this_leaf->level == 2));
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
}

static void cache_cpumap_setup(unsigned int cpu)
{
<<<<<<< HEAD
	unsigned int index;
	struct cacheinfo *this_leaf, *sib_leaf;
	struct cpu_cacheinfo *this_cpu_ci = get_cpu_cacheinfo(cpu);
=======
	struct cpu_cacheinfo *this_cpu_ci = get_cpu_cacheinfo(cpu);
	struct cacheinfo *this_leaf, *sib_leaf;
	unsigned int index;
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2

	for (index = 0; index < this_cpu_ci->num_leaves; index++) {
		unsigned int i;

		this_leaf = this_cpu_ci->info_list + index;
		/* skip if shared_cpu_map is already populated */
		if (!cpumask_empty(&this_leaf->shared_cpu_map))
			continue;

		cpumask_set_cpu(cpu, &this_leaf->shared_cpu_map);
		for_each_online_cpu(i) {
			struct cpu_cacheinfo *sib_cpu_ci = get_cpu_cacheinfo(i);

<<<<<<< HEAD
			if (i == cpu || !sib_cpu_ci->info_list ||
				(cpu_to_node(i) != cpu_to_node(cpu)))
				continue;

=======
			if (i == cpu || !sib_cpu_ci->info_list)
				continue;/* skip if itself or no cacheinfo */
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
			sib_leaf = sib_cpu_ci->info_list + index;
			if (cache_leaves_are_shared(this_leaf, sib_leaf)) {
				cpumask_set_cpu(cpu, &sib_leaf->shared_cpu_map);
				cpumask_set_cpu(i, &this_leaf->shared_cpu_map);
			}
		}
	}
}

int populate_cache_leaves(unsigned int cpu)
{
<<<<<<< HEAD
	int i, cache_present = current_cpu_data.cache_leaves_present;
	struct cpu_cacheinfo *this_cpu_ci = get_cpu_cacheinfo(cpu);
	struct cacheinfo *this_leaf = this_cpu_ci->info_list;
	struct cache_desc *cd, *cdesc = current_cpu_data.cache_leaves;

	for (i = 0; i < cache_present; i++) {
		cd = cdesc + i;

		this_leaf->type = cd->type;
		this_leaf->level = cd->level;
		this_leaf->coherency_line_size = cd->linesz;
		this_leaf->number_of_sets = cd->sets;
		this_leaf->ways_of_associativity = cd->ways;
		this_leaf->size = cd->linesz * cd->sets * cd->ways;
		this_leaf->priv = &cd->flags;
		this_leaf++;
	}

=======
	int level = 1, nodes_per_package = 1;
	struct cpuinfo_loongarch *c = &current_cpu_data;
	struct cpu_cacheinfo *this_cpu_ci = get_cpu_cacheinfo(cpu);
	struct cacheinfo *this_leaf = this_cpu_ci->info_list;

	if (loongson_sysconf.nr_nodes > 1)
		nodes_per_package = loongson_sysconf.cores_per_package
					/ loongson_sysconf.cores_per_node;

	if (c->icache.waysize) {
		populate_cache(dcache, this_leaf, level, CACHE_TYPE_DATA);
		populate_cache(icache, this_leaf, level++, CACHE_TYPE_INST);
	} else {
		populate_cache(dcache, this_leaf, level++, CACHE_TYPE_UNIFIED);
	}

	if (c->vcache.waysize)
		populate_cache(vcache, this_leaf, level++, CACHE_TYPE_UNIFIED);

	if (c->scache.waysize)
		populate_cache(scache, this_leaf, level++, CACHE_TYPE_UNIFIED);

	if (c->tcache.waysize)
		populate_cache(tcache, this_leaf, level++, CACHE_TYPE_UNIFIED);

>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
	cache_cpumap_setup(cpu);
	this_cpu_ci->cpu_map_populated = true;

	return 0;
}
