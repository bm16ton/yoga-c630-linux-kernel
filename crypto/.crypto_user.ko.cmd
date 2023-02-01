cmd_crypto/crypto_user.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o crypto/crypto_user.ko crypto/crypto_user.o crypto/crypto_user.mod.o;  true
