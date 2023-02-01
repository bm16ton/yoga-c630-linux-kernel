cmd_drivers/ata/libata.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/ata/libata.ko drivers/ata/libata.o drivers/ata/libata.mod.o;  true
