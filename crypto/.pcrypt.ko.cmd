cmd_crypto/pcrypt.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o crypto/pcrypt.ko crypto/pcrypt.o crypto/pcrypt.mod.o;  true
