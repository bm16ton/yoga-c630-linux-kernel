cmd_init/built-in.a := rm -f init/built-in.a;  printf "init/%s " main.o version.o do_mounts.o do_mounts_initrd.o initramfs.o calibrate.o init_task.o | xargs ar cDPrST init/built-in.a
