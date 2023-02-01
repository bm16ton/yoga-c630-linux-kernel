cmd_crypto/anubis.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o crypto/anubis.ko crypto/anubis.o crypto/anubis.mod.o;  true
