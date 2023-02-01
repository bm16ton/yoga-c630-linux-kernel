cmd_drivers/mtd/rfd_ftl.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/mtd/rfd_ftl.ko drivers/mtd/rfd_ftl.o drivers/mtd/rfd_ftl.mod.o;  true
