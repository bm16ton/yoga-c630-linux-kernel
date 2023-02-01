cmd_drivers/md/dm-crypt.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/md/dm-crypt.ko drivers/md/dm-crypt.o drivers/md/dm-crypt.mod.o;  true
