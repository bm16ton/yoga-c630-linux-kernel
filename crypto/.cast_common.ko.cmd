cmd_crypto/cast_common.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o crypto/cast_common.ko crypto/cast_common.o crypto/cast_common.mod.o;  true
