cmd_drivers/block/loop.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/block/loop.ko drivers/block/loop.o drivers/block/loop.mod.o;  true
