cmd_drivers/mtd/nand/raw/built-in.a := rm -f drivers/mtd/nand/raw/built-in.a;  printf "drivers/mtd/nand/raw/%s " ingenic/built-in.a | xargs ar cDPrST drivers/mtd/nand/raw/built-in.a
