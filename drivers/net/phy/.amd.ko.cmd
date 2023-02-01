cmd_drivers/net/phy/amd.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/net/phy/amd.ko drivers/net/phy/amd.o drivers/net/phy/amd.mod.o;  true
