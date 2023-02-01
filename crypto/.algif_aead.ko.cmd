cmd_crypto/algif_aead.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o crypto/algif_aead.ko crypto/algif_aead.o crypto/algif_aead.mod.o;  true
