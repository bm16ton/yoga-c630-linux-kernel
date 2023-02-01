cmd_drivers/atm/solos-pci.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/atm/solos-pci.ko drivers/atm/solos-pci.o drivers/atm/solos-pci.mod.o;  true
