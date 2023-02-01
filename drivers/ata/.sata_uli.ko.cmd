cmd_drivers/ata/sata_uli.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/ata/sata_uli.ko drivers/ata/sata_uli.o drivers/ata/sata_uli.mod.o;  true
