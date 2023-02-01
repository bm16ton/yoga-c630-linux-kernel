cmd_lib/crypto/libdes.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o lib/crypto/libdes.ko lib/crypto/libdes.o lib/crypto/libdes.mod.o;  true
