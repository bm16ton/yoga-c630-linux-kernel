cmd_drivers/nfc/fdp/fdp.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/nfc/fdp/fdp.ko drivers/nfc/fdp/fdp.o drivers/nfc/fdp/fdp.mod.o;  true
