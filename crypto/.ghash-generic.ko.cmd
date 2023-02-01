cmd_crypto/ghash-generic.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o crypto/ghash-generic.ko crypto/ghash-generic.o crypto/ghash-generic.mod.o;  true
