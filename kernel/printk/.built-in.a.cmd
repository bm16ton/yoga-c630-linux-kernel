cmd_kernel/printk/built-in.a := rm -f kernel/printk/built-in.a;  printf "kernel/printk/%s " printk.o printk_safe.o braille.o printk_ringbuffer.o sysctl.o | xargs ar cDPrST kernel/printk/built-in.a
