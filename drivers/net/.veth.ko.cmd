cmd_drivers/net/veth.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/net/veth.ko drivers/net/veth.o drivers/net/veth.mod.o;  true
