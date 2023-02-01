cmd_drivers/md/dm-era.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/md/dm-era.ko drivers/md/dm-era.o drivers/md/dm-era.mod.o;  true
