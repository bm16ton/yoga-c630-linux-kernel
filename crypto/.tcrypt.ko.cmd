cmd_crypto/tcrypt.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o crypto/tcrypt.ko crypto/tcrypt.o crypto/tcrypt.mod.o;  true
