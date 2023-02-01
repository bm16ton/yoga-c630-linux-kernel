cmd_crypto/fcrypt.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o crypto/fcrypt.ko crypto/fcrypt.o crypto/fcrypt.mod.o;  true
