cmd_drivers/ata/sata_mv.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/ata/sata_mv.ko drivers/ata/sata_mv.o drivers/ata/sata_mv.mod.o;  true
