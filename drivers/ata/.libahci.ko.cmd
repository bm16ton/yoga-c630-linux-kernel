cmd_drivers/ata/libahci.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/ata/libahci.ko drivers/ata/libahci.o drivers/ata/libahci.mod.o;  true
