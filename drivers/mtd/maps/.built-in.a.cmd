cmd_drivers/mtd/maps/built-in.a := rm -f drivers/mtd/maps/built-in.a;  printf "drivers/mtd/maps/%s " map_funcs.o | xargs ar cDPrST drivers/mtd/maps/built-in.a
