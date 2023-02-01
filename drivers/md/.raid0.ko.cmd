cmd_drivers/md/raid0.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/md/raid0.ko drivers/md/raid0.o drivers/md/raid0.mod.o;  true
