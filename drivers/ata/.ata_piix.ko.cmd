cmd_drivers/ata/ata_piix.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/ata/ata_piix.ko drivers/ata/ata_piix.o drivers/ata/ata_piix.mod.o;  true
