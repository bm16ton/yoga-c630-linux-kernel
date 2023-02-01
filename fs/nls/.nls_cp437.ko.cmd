cmd_fs/nls/nls_cp437.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o fs/nls/nls_cp437.ko fs/nls/nls_cp437.o fs/nls/nls_cp437.mod.o;  true
