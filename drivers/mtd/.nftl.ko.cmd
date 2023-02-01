cmd_drivers/mtd/nftl.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/mtd/nftl.ko drivers/mtd/nftl.o drivers/mtd/nftl.mod.o;  true
