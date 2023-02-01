cmd_fs/nls/nls_iso8859-1.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o fs/nls/nls_iso8859-1.ko fs/nls/nls_iso8859-1.o fs/nls/nls_iso8859-1.mod.o;  true
