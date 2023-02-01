cmd_drivers/mtd/ssfdc.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/mtd/ssfdc.ko drivers/mtd/ssfdc.o drivers/mtd/ssfdc.mod.o;  true
