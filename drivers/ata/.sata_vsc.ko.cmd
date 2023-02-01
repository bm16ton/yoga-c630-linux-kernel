cmd_drivers/ata/sata_vsc.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/ata/sata_vsc.ko drivers/ata/sata_vsc.o drivers/ata/sata_vsc.mod.o;  true
