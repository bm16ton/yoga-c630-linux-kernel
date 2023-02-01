cmd_drivers/net/ifb.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/net/ifb.ko drivers/net/ifb.o drivers/net/ifb.mod.o;  true
