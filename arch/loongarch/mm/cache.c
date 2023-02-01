// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2020-2022 Loongson Technology Corporation Limited
 *
 * Derived from MIPS:
 * Copyright (C) 1994 - 2003, 06, 07 by Ralf Baechle (ralf@linux-mips.org)
 * Copyright (C) 2007 MIPS Technologies, Inc.
 */
<<<<<<< HEAD
#include <linux/cacheinfo.h>
#include <linux/export.h>
=======
#include <linux/export.h>
#include <linux/fcntl.h>
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
#include <linux/fs.h>
#include <linux/highmem.h>
#include <linux/kernel.h>
#include <linux/linkage.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/syscalls.h>

<<<<<<< HEAD
#include <asm/bootinfo.h>
#include <asm/cacheflush.h>
#include <asm/cpu.h>
#include <asm/cpu-features.h>
#include <asm/loongarch.h>
#include <asm/numa.h>
#include <asm/processor.h>
#include <asm/setup.h>

void cache_error_setup(void)
{
	extern char __weak except_vec_cex;
	set_merr_handler(0x0, &except_vec_cex, 0x80);
}

=======
#include <asm/cacheflush.h>
#include <asm/cpu.h>
#include <asm/cpu-features.h>
#include <asm/dma.h>
#include <asm/loongarch.h>
#include <asm/processor.h>
#include <asm/setup.h>

>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
/*
 * LoongArch maintains ICache/DCache coherency by hardware,
 * we just need "ibar" to avoid instruction hazard here.
 */
void local_flush_icache_range(unsigned long start, unsigned long end)
{
	asm volatile ("\tibar 0\n"::);
}
EXPORT_SYMBOL(local_flush_icache_range);

<<<<<<< HEAD
static void flush_cache_leaf(unsigned int leaf)
{
	int i, j, nr_nodes;
	uint64_t addr = CSR_DMW0_BASE;
	struct cache_desc *cdesc = current_cpu_data.cache_leaves + leaf;

	nr_nodes = cache_private(cdesc) ? 1 : loongson_sysconf.nr_nodes;

	do {
		for (i = 0; i < cdesc->sets; i++) {
			for (j = 0; j < cdesc->ways; j++) {
				flush_cache_line(leaf, addr);
				addr++;
			}

			addr -= cdesc->ways;
			addr += cdesc->linesz;
		}
		addr += (1ULL << NODE_ADDRSPACE_SHIFT);
	} while (--nr_nodes > 0);
}

asmlinkage __visible void __flush_cache_all(void)
{
	int leaf;
	struct cache_desc *cdesc = current_cpu_data.cache_leaves;
	unsigned int cache_present = current_cpu_data.cache_leaves_present;

	leaf = cache_present - 1;
	if (cache_inclusive(cdesc + leaf)) {
		flush_cache_leaf(leaf);
		return;
	}

	for (leaf = 0; leaf < cache_present; leaf++)
		flush_cache_leaf(leaf);
}

#define L1IUPRE		(1 << 0)
#define L1IUUNIFY	(1 << 1)
#define L1DPRE		(1 << 2)

#define LXIUPRE		(1 << 0)
#define LXIUUNIFY	(1 << 1)
#define LXIUPRIV	(1 << 2)
#define LXIUINCL	(1 << 3)
#define LXDPRE		(1 << 4)
#define LXDPRIV		(1 << 5)
#define LXDINCL		(1 << 6)

#define populate_cache_properties(cfg0, cdesc, level, leaf)				\
do {											\
	unsigned int cfg1;								\
											\
	cfg1 = read_cpucfg(LOONGARCH_CPUCFG17 + leaf);					\
	if (level == 1)	{								\
		cdesc->flags |= CACHE_PRIVATE;						\
	} else {									\
		if (cfg0 & LXIUPRIV)							\
			cdesc->flags |= CACHE_PRIVATE;					\
		if (cfg0 & LXIUINCL)							\
			cdesc->flags |= CACHE_INCLUSIVE;				\
	}										\
	cdesc->level = level;								\
	cdesc->flags |= CACHE_PRESENT;							\
	cdesc->ways = ((cfg1 & CPUCFG_CACHE_WAYS_M) >> CPUCFG_CACHE_WAYS) + 1;		\
	cdesc->sets = 1 << ((cfg1 & CPUCFG_CACHE_SETS_M) >> CPUCFG_CACHE_SETS);		\
	cdesc->linesz = 1 << ((cfg1 & CPUCFG_CACHE_LSIZE_M) >> CPUCFG_CACHE_LSIZE);	\
	cdesc++; leaf++;								\
} while (0)

void cpu_cache_init(void)
{
	unsigned int leaf = 0, level = 1;
	unsigned int config = read_cpucfg(LOONGARCH_CPUCFG16);
	struct cache_desc *cdesc = current_cpu_data.cache_leaves;

	if (config & L1IUPRE) {
		if (config & L1IUUNIFY)
			cdesc->type = CACHE_TYPE_UNIFIED;
		else
			cdesc->type = CACHE_TYPE_INST;
		populate_cache_properties(config, cdesc, level, leaf);
	}

	if (config & L1DPRE) {
		cdesc->type = CACHE_TYPE_DATA;
		populate_cache_properties(config, cdesc, level, leaf);
	}

	config = config >> 3;
	for (level = 2; level <= CACHE_LEVEL_MAX; level++) {
		if (!config)
			break;

		if (config & LXIUPRE) {
			if (config & LXIUUNIFY)
				cdesc->type = CACHE_TYPE_UNIFIED;
			else
				cdesc->type = CACHE_TYPE_INST;
			populate_cache_properties(config, cdesc, level, leaf);
		}

		if (config & LXDPRE) {
			cdesc->type = CACHE_TYPE_DATA;
			populate_cache_properties(config, cdesc, level, leaf);
		}

		config = config >> 7;
	}

	BUG_ON(leaf > CACHE_LEAVES_MAX);

	current_cpu_data.cache_leaves_present = leaf;
	current_cpu_data.options |= LOONGARCH_CPU_PREFETCH;
=======
void cache_error_setup(void)
{
	extern char __weak except_vec_cex;
	set_merr_handler(0x0, &except_vec_cex, 0x80);
}

static unsigned long icache_size __read_mostly;
static unsigned long dcache_size __read_mostly;
static unsigned long vcache_size __read_mostly;
static unsigned long scache_size __read_mostly;

static char *way_string[] = { NULL, "direct mapped", "2-way",
	"3-way", "4-way", "5-way", "6-way", "7-way", "8-way",
	"9-way", "10-way", "11-way", "12-way",
	"13-way", "14-way", "15-way", "16-way",
};

static void probe_pcache(void)
{
	struct cpuinfo_loongarch *c = &current_cpu_data;
	unsigned int lsize, sets, ways;
	unsigned int config;

	config = read_cpucfg(LOONGARCH_CPUCFG17);
	lsize = 1 << ((config & CPUCFG17_L1I_SIZE_M) >> CPUCFG17_L1I_SIZE);
	sets  = 1 << ((config & CPUCFG17_L1I_SETS_M) >> CPUCFG17_L1I_SETS);
	ways  = ((config & CPUCFG17_L1I_WAYS_M) >> CPUCFG17_L1I_WAYS) + 1;

	c->icache.linesz = lsize;
	c->icache.sets = sets;
	c->icache.ways = ways;
	icache_size = sets * ways * lsize;
	c->icache.waysize = icache_size / c->icache.ways;

	config = read_cpucfg(LOONGARCH_CPUCFG18);
	lsize = 1 << ((config & CPUCFG18_L1D_SIZE_M) >> CPUCFG18_L1D_SIZE);
	sets  = 1 << ((config & CPUCFG18_L1D_SETS_M) >> CPUCFG18_L1D_SETS);
	ways  = ((config & CPUCFG18_L1D_WAYS_M) >> CPUCFG18_L1D_WAYS) + 1;

	c->dcache.linesz = lsize;
	c->dcache.sets = sets;
	c->dcache.ways = ways;
	dcache_size = sets * ways * lsize;
	c->dcache.waysize = dcache_size / c->dcache.ways;

	c->options |= LOONGARCH_CPU_PREFETCH;

	pr_info("Primary instruction cache %ldkB, %s, %s, linesize %d bytes.\n",
		icache_size >> 10, way_string[c->icache.ways], "VIPT", c->icache.linesz);

	pr_info("Primary data cache %ldkB, %s, %s, %s, linesize %d bytes\n",
		dcache_size >> 10, way_string[c->dcache.ways], "VIPT", "no aliases", c->dcache.linesz);
}

static void probe_vcache(void)
{
	struct cpuinfo_loongarch *c = &current_cpu_data;
	unsigned int lsize, sets, ways;
	unsigned int config;

	config = read_cpucfg(LOONGARCH_CPUCFG19);
	lsize = 1 << ((config & CPUCFG19_L2_SIZE_M) >> CPUCFG19_L2_SIZE);
	sets  = 1 << ((config & CPUCFG19_L2_SETS_M) >> CPUCFG19_L2_SETS);
	ways  = ((config & CPUCFG19_L2_WAYS_M) >> CPUCFG19_L2_WAYS) + 1;

	c->vcache.linesz = lsize;
	c->vcache.sets = sets;
	c->vcache.ways = ways;
	vcache_size = lsize * sets * ways;
	c->vcache.waysize = vcache_size / c->vcache.ways;

	pr_info("Unified victim cache %ldkB %s, linesize %d bytes.\n",
		vcache_size >> 10, way_string[c->vcache.ways], c->vcache.linesz);
}

static void probe_scache(void)
{
	struct cpuinfo_loongarch *c = &current_cpu_data;
	unsigned int lsize, sets, ways;
	unsigned int config;

	config = read_cpucfg(LOONGARCH_CPUCFG20);
	lsize = 1 << ((config & CPUCFG20_L3_SIZE_M) >> CPUCFG20_L3_SIZE);
	sets  = 1 << ((config & CPUCFG20_L3_SETS_M) >> CPUCFG20_L3_SETS);
	ways  = ((config & CPUCFG20_L3_WAYS_M) >> CPUCFG20_L3_WAYS) + 1;

	c->scache.linesz = lsize;
	c->scache.sets = sets;
	c->scache.ways = ways;
	/* 4 cores. scaches are shared */
	scache_size = lsize * sets * ways;
	c->scache.waysize = scache_size / c->scache.ways;

	pr_info("Unified secondary cache %ldkB %s, linesize %d bytes.\n",
		scache_size >> 10, way_string[c->scache.ways], c->scache.linesz);
}

void cpu_cache_init(void)
{
	probe_pcache();
	probe_vcache();
	probe_scache();

>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
	shm_align_mask = PAGE_SIZE - 1;
}

static const pgprot_t protection_map[16] = {
	[VM_NONE]					= __pgprot(_CACHE_CC | _PAGE_USER |
								   _PAGE_PROTNONE | _PAGE_NO_EXEC |
								   _PAGE_NO_READ),
	[VM_READ]					= __pgprot(_CACHE_CC | _PAGE_VALID |
								   _PAGE_USER | _PAGE_PRESENT |
								   _PAGE_NO_EXEC),
	[VM_WRITE]					= __pgprot(_CACHE_CC | _PAGE_VALID |
								   _PAGE_USER | _PAGE_PRESENT |
								   _PAGE_NO_EXEC),
	[VM_WRITE | VM_READ]				= __pgprot(_CACHE_CC | _PAGE_VALID |
								   _PAGE_USER | _PAGE_PRESENT |
								   _PAGE_NO_EXEC),
	[VM_EXEC]					= __pgprot(_CACHE_CC | _PAGE_VALID |
								   _PAGE_USER | _PAGE_PRESENT),
	[VM_EXEC | VM_READ]				= __pgprot(_CACHE_CC | _PAGE_VALID |
								   _PAGE_USER | _PAGE_PRESENT),
	[VM_EXEC | VM_WRITE]				= __pgprot(_CACHE_CC | _PAGE_VALID |
								   _PAGE_USER | _PAGE_PRESENT),
	[VM_EXEC | VM_WRITE | VM_READ]			= __pgprot(_CACHE_CC | _PAGE_VALID |
								   _PAGE_USER | _PAGE_PRESENT),
	[VM_SHARED]					= __pgprot(_CACHE_CC | _PAGE_USER |
								   _PAGE_PROTNONE | _PAGE_NO_EXEC |
								   _PAGE_NO_READ),
	[VM_SHARED | VM_READ]				= __pgprot(_CACHE_CC | _PAGE_VALID |
								   _PAGE_USER | _PAGE_PRESENT |
								   _PAGE_NO_EXEC),
	[VM_SHARED | VM_WRITE]				= __pgprot(_CACHE_CC | _PAGE_VALID |
								   _PAGE_USER | _PAGE_PRESENT |
								   _PAGE_NO_EXEC | _PAGE_WRITE),
	[VM_SHARED | VM_WRITE | VM_READ]		= __pgprot(_CACHE_CC | _PAGE_VALID |
								   _PAGE_USER | _PAGE_PRESENT |
								   _PAGE_NO_EXEC | _PAGE_WRITE),
	[VM_SHARED | VM_EXEC]				= __pgprot(_CACHE_CC | _PAGE_VALID |
								   _PAGE_USER | _PAGE_PRESENT),
	[VM_SHARED | VM_EXEC | VM_READ]			= __pgprot(_CACHE_CC | _PAGE_VALID |
								   _PAGE_USER | _PAGE_PRESENT),
	[VM_SHARED | VM_EXEC | VM_WRITE]		= __pgprot(_CACHE_CC | _PAGE_VALID |
								   _PAGE_USER | _PAGE_PRESENT |
								   _PAGE_WRITE),
	[VM_SHARED | VM_EXEC | VM_WRITE | VM_READ]	= __pgprot(_CACHE_CC | _PAGE_VALID |
								   _PAGE_USER | _PAGE_PRESENT |
								   _PAGE_WRITE)
};
DECLARE_VM_GET_PAGE_PROT
