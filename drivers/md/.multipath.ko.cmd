cmd_drivers/md/multipath.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/md/multipath.ko drivers/md/multipath.o drivers/md/multipath.mod.o;  true
