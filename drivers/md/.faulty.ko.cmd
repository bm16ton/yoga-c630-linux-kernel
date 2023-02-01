cmd_drivers/md/faulty.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/md/faulty.ko drivers/md/faulty.o drivers/md/faulty.mod.o;  true
