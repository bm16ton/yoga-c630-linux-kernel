cmd_net/nfc/hci/hci.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/nfc/hci/hci.ko net/nfc/hci/hci.o net/nfc/hci/hci.mod.o;  true
