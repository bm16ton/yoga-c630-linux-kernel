cmd_crypto/algif_rng.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o crypto/algif_rng.ko crypto/algif_rng.o crypto/algif_rng.mod.o;  true
