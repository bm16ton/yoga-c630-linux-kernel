cmd_kernel/module/built-in.a := rm -f kernel/module/built-in.a;  printf "kernel/module/%s " main.o strict_rwx.o tree_lookup.o kallsyms.o procfs.o sysfs.o | xargs ar cDPrST kernel/module/built-in.a
