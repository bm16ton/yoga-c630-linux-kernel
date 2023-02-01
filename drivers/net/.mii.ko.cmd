cmd_drivers/net/mii.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/net/mii.ko drivers/net/mii.o drivers/net/mii.mod.o;  true
