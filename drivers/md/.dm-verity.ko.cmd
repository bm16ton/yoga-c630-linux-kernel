cmd_drivers/md/dm-verity.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/md/dm-verity.ko drivers/md/dm-verity.o drivers/md/dm-verity.mod.o;  true
