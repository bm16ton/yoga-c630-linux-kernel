cmd_drivers/md/built-in.a := rm -f drivers/md/built-in.a;  printf "drivers/md/%s " dm-builtin.o | xargs ar cDPrST drivers/md/built-in.a
