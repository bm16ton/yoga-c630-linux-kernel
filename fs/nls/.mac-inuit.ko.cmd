cmd_fs/nls/mac-inuit.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o fs/nls/mac-inuit.ko fs/nls/mac-inuit.o fs/nls/mac-inuit.mod.o;  true
