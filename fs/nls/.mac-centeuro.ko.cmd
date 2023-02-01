cmd_fs/nls/mac-centeuro.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o fs/nls/mac-centeuro.ko fs/nls/mac-centeuro.o fs/nls/mac-centeuro.mod.o;  true
