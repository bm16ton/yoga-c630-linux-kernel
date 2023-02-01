cmd_drivers/mtd/sm_ftl.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/mtd/sm_ftl.ko drivers/mtd/sm_ftl.o drivers/mtd/sm_ftl.mod.o;  true
