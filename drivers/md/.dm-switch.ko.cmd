cmd_drivers/md/dm-switch.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/md/dm-switch.ko drivers/md/dm-switch.o drivers/md/dm-switch.mod.o;  true
