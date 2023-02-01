cmd_crypto/cast6_generic.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o crypto/cast6_generic.ko crypto/cast6_generic.o crypto/cast6_generic.mod.o;  true
