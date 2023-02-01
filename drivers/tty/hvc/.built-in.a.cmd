cmd_drivers/tty/hvc/built-in.a := rm -f drivers/tty/hvc/built-in.a;  printf "drivers/tty/hvc/%s " hvc_console.o hvc_irq.o hvc_xen.o | xargs ar cDPrST drivers/tty/hvc/built-in.a
