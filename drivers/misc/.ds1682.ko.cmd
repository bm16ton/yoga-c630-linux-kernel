cmd_drivers/misc/ds1682.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/misc/ds1682.ko drivers/misc/ds1682.o drivers/misc/ds1682.mod.o;  true
