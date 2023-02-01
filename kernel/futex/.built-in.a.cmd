cmd_kernel/futex/built-in.a := rm -f kernel/futex/built-in.a;  printf "kernel/futex/%s " core.o syscalls.o pi.o requeue.o waitwake.o | xargs ar cDPrST kernel/futex/built-in.a
