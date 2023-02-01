cmd_drivers/block/rbd.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/block/rbd.ko drivers/block/rbd.o drivers/block/rbd.mod.o;  true
