cmd_drivers/dax/dax.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/dax/dax.ko drivers/dax/dax.o drivers/dax/dax.mod.o;  true
