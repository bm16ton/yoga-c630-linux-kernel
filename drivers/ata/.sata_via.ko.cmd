cmd_drivers/ata/sata_via.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/ata/sata_via.ko drivers/ata/sata_via.o drivers/ata/sata_via.mod.o;  true
