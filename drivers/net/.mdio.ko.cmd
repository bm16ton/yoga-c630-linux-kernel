cmd_drivers/net/mdio.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/net/mdio.ko drivers/net/mdio.o drivers/net/mdio.mod.o;  true
