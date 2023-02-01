cmd_crypto/xxhash_generic.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o crypto/xxhash_generic.ko crypto/xxhash_generic.o crypto/xxhash_generic.mod.o;  true
