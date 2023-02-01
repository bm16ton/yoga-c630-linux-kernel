cmd_drivers/md/dm-delay.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/md/dm-delay.ko drivers/md/dm-delay.o drivers/md/dm-delay.mod.o;  true
