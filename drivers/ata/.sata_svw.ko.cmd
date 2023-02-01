cmd_drivers/ata/sata_svw.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/ata/sata_svw.ko drivers/ata/sata_svw.o drivers/ata/sata_svw.mod.o;  true
