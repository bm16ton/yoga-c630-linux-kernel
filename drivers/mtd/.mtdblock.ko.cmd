cmd_drivers/mtd/mtdblock.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/mtd/mtdblock.ko drivers/mtd/mtdblock.o drivers/mtd/mtdblock.mod.o;  true
