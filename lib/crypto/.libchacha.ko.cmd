cmd_lib/crypto/libchacha.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o lib/crypto/libchacha.ko lib/crypto/libchacha.o lib/crypto/libchacha.mod.o;  true
