cmd_crypto/michael_mic.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o crypto/michael_mic.ko crypto/michael_mic.o crypto/michael_mic.mod.o;  true
