cmd_drivers/net/slip/slip.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/net/slip/slip.ko drivers/net/slip/slip.o drivers/net/slip/slip.mod.o;  true
