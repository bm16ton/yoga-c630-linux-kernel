/* SPDX-License-Identifier: GPL-2.0 */

#ifndef _NF_CONNTRACK_BPF_H
#define _NF_CONNTRACK_BPF_H

<<<<<<< HEAD
#include <linux/kconfig.h>
#include <net/netfilter/nf_conntrack.h>

struct nf_conn___init {
	struct nf_conn ct;
};
=======
#include <linux/btf.h>
#include <linux/kconfig.h>
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2

#if (IS_BUILTIN(CONFIG_NF_CONNTRACK) && IS_ENABLED(CONFIG_DEBUG_INFO_BTF)) || \
    (IS_MODULE(CONFIG_NF_CONNTRACK) && IS_ENABLED(CONFIG_DEBUG_INFO_BTF_MODULES))

extern int register_nf_conntrack_bpf(void);
<<<<<<< HEAD
extern void cleanup_nf_conntrack_bpf(void);
=======
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2

#else

static inline int register_nf_conntrack_bpf(void)
{
	return 0;
}

<<<<<<< HEAD
static inline void cleanup_nf_conntrack_bpf(void)
{
}

#endif

#if (IS_BUILTIN(CONFIG_NF_NAT) && IS_ENABLED(CONFIG_DEBUG_INFO_BTF)) || \
    (IS_MODULE(CONFIG_NF_NAT) && IS_ENABLED(CONFIG_DEBUG_INFO_BTF_MODULES))

extern int register_nf_nat_bpf(void);

#else

static inline int register_nf_nat_bpf(void)
{
	return 0;
}

=======
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
#endif

#endif /* _NF_CONNTRACK_BPF_H */
