cmd_fs/nls/mac-roman.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o fs/nls/mac-roman.ko fs/nls/mac-roman.o fs/nls/mac-roman.mod.o;  true
