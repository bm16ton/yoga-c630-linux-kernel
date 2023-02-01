cmd_drivers/ata/sata_sil.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/ata/sata_sil.ko drivers/ata/sata_sil.o drivers/ata/sata_sil.mod.o;  true
