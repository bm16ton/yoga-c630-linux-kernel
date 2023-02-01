cmd_fs/nls/nls_utf8.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o fs/nls/nls_utf8.ko fs/nls/nls_utf8.o fs/nls/nls_utf8.mod.o;  true
