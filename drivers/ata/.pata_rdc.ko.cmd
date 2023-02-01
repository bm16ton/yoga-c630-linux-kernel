cmd_drivers/ata/pata_rdc.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/ata/pata_rdc.ko drivers/ata/pata_rdc.o drivers/ata/pata_rdc.mod.o;  true
