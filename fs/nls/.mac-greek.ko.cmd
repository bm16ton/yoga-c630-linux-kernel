cmd_fs/nls/mac-greek.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o fs/nls/mac-greek.ko fs/nls/mac-greek.o fs/nls/mac-greek.mod.o;  true
