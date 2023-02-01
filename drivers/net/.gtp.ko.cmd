cmd_drivers/net/gtp.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/net/gtp.ko drivers/net/gtp.o drivers/net/gtp.mod.o;  true
