cmd_lib/test_printf.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o lib/test_printf.ko lib/test_printf.o lib/test_printf.mod.o;  true
