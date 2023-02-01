cmd_drivers/ata/sata_sis.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/ata/sata_sis.ko drivers/ata/sata_sis.o drivers/ata/sata_sis.mod.o;  true
