cmd_drivers/block/nbd.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/block/nbd.ko drivers/block/nbd.o drivers/block/nbd.mod.o;  true
