cmd_drivers/block/aoe/aoe.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/block/aoe/aoe.ko drivers/block/aoe/aoe.o drivers/block/aoe/aoe.mod.o;  true
