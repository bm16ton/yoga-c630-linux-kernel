cmd_crypto/chacha_generic.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o crypto/chacha_generic.ko crypto/chacha_generic.o crypto/chacha_generic.mod.o;  true
