cmd_drivers/phy/phy-xgene.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/phy/phy-xgene.ko drivers/phy/phy-xgene.o drivers/phy/phy-xgene.mod.o;  true
