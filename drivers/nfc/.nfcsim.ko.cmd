cmd_drivers/nfc/nfcsim.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/nfc/nfcsim.ko drivers/nfc/nfcsim.o drivers/nfc/nfcsim.mod.o;  true
