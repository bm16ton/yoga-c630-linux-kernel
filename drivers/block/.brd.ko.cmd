cmd_drivers/block/brd.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/block/brd.ko drivers/block/brd.o drivers/block/brd.mod.o;  true
