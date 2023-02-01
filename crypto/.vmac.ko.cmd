cmd_crypto/vmac.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o crypto/vmac.ko crypto/vmac.o crypto/vmac.mod.o;  true
