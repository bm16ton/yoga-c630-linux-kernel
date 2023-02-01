cmd_kernel/events/built-in.a := rm -f kernel/events/built-in.a;  printf "kernel/events/%s " core.o ring_buffer.o callchain.o hw_breakpoint.o uprobes.o | xargs ar cDPrST kernel/events/built-in.a
