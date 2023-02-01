cmd_fs/befs/befs.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o fs/befs/befs.ko fs/befs/befs.o fs/befs/befs.mod.o;  true
