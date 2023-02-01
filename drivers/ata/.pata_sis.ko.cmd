cmd_drivers/ata/pata_sis.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/ata/pata_sis.ko drivers/ata/pata_sis.o drivers/ata/pata_sis.mod.o;  true
