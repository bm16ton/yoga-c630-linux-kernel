cmd_drivers/ata/sata_sx4.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/ata/sata_sx4.ko drivers/ata/sata_sx4.o drivers/ata/sata_sx4.mod.o;  true
