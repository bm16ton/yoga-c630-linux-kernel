cmd_drivers/ata/pdc_adma.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/ata/pdc_adma.ko drivers/ata/pdc_adma.o drivers/ata/pdc_adma.mod.o;  true
