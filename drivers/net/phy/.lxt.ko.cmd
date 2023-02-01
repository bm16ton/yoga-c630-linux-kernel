cmd_drivers/net/phy/lxt.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/net/phy/lxt.ko drivers/net/phy/lxt.o drivers/net/phy/lxt.mod.o;  true
