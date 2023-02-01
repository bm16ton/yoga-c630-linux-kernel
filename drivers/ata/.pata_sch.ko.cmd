cmd_drivers/ata/pata_sch.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/ata/pata_sch.ko drivers/ata/pata_sch.o drivers/ata/pata_sch.mod.o;  true
