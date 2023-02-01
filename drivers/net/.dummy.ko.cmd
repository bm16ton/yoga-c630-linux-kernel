cmd_drivers/net/dummy.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/net/dummy.ko drivers/net/dummy.o drivers/net/dummy.mod.o;  true
