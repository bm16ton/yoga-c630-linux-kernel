cmd_crypto/tea.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o crypto/tea.ko crypto/tea.o crypto/tea.mod.o;  true
