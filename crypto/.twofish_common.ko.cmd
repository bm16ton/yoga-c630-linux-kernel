cmd_crypto/twofish_common.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o crypto/twofish_common.ko crypto/twofish_common.o crypto/twofish_common.mod.o;  true
