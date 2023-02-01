cmd_lib/test_user_copy.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o lib/test_user_copy.ko lib/test_user_copy.o lib/test_user_copy.mod.o;  true
