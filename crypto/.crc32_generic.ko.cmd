cmd_crypto/crc32_generic.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o crypto/crc32_generic.ko crypto/crc32_generic.o crypto/crc32_generic.mod.o;  true
