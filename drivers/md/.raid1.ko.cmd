cmd_drivers/md/raid1.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/md/raid1.ko drivers/md/raid1.o drivers/md/raid1.mod.o;  true
