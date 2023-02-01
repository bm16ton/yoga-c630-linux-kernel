cmd_lib/test_static_keys.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o lib/test_static_keys.ko lib/test_static_keys.o lib/test_static_keys.mod.o;  true
