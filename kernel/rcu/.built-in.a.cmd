cmd_kernel/rcu/built-in.a := rm -f kernel/rcu/built-in.a;  printf "kernel/rcu/%s " update.o sync.o srcutree.o tree.o rcu_segcblist.o | xargs ar cDPrST kernel/rcu/built-in.a
