cmd_drivers/mtd/ubi/ubi.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/mtd/ubi/ubi.ko drivers/mtd/ubi/ubi.o drivers/mtd/ubi/ubi.mod.o;  true
