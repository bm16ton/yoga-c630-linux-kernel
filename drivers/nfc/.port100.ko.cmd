cmd_drivers/nfc/port100.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/nfc/port100.ko drivers/nfc/port100.o drivers/nfc/port100.mod.o;  true
