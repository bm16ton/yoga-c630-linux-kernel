cmd_drivers/md/dm-zero.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/md/dm-zero.ko drivers/md/dm-zero.o drivers/md/dm-zero.mod.o;  true
