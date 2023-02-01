cmd_drivers/net/vsockmon.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/net/vsockmon.ko drivers/net/vsockmon.o drivers/net/vsockmon.mod.o;  true
