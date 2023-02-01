cmd_drivers/net/slip/slhc.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/net/slip/slhc.ko drivers/net/slip/slhc.o drivers/net/slip/slhc.mod.o;  true
