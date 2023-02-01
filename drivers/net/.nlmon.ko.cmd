cmd_drivers/net/nlmon.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/net/nlmon.ko drivers/net/nlmon.o drivers/net/nlmon.mod.o;  true
