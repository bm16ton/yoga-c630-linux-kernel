cmd_drivers/ata/sata_nv.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/ata/sata_nv.ko drivers/ata/sata_nv.o drivers/ata/sata_nv.mod.o;  true
