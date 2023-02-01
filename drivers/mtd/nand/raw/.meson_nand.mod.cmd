cmd_drivers/mtd/nand/raw/meson_nand.mod := printf '%s\n'   meson_nand.o | awk '!x[$$0]++ { print("drivers/mtd/nand/raw/"$$0) }' > drivers/mtd/nand/raw/meson_nand.mod
