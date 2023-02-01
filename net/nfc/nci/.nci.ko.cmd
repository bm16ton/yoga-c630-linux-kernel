cmd_net/nfc/nci/nci.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/nfc/nci/nci.ko net/nfc/nci/nci.o net/nfc/nci/nci.mod.o;  true
