cmd_drivers/xen/events/built-in.a := rm -f drivers/xen/events/built-in.a;  printf "drivers/xen/events/%s " events_base.o events_2l.o events_fifo.o | xargs ar cDPrST drivers/xen/events/built-in.a
