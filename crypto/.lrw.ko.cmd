cmd_crypto/lrw.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o crypto/lrw.ko crypto/lrw.o crypto/lrw.mod.o;  true
