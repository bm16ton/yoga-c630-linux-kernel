cmd_crypto/pcbc.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o crypto/pcbc.ko crypto/pcbc.o crypto/pcbc.mod.o;  true
