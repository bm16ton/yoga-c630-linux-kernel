cmd_drivers/md/raid456.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/md/raid456.ko drivers/md/raid456.o drivers/md/raid456.mod.o;  true
