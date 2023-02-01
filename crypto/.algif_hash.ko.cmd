cmd_crypto/algif_hash.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o crypto/algif_hash.ko crypto/algif_hash.o crypto/algif_hash.mod.o;  true
