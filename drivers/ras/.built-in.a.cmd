cmd_drivers/ras/built-in.a := rm -f drivers/ras/built-in.a;  printf "drivers/ras/%s " ras.o debugfs.o | xargs ar cDPrST drivers/ras/built-in.a
