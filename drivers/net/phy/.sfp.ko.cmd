cmd_drivers/net/phy/sfp.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/net/phy/sfp.ko drivers/net/phy/sfp.o drivers/net/phy/sfp.mod.o;  true
