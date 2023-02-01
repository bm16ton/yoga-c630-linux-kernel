cmd_drivers/net/phy/qsemi.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/net/phy/qsemi.ko drivers/net/phy/qsemi.o drivers/net/phy/qsemi.mod.o;  true
