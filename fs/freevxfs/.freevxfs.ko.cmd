cmd_fs/freevxfs/freevxfs.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o fs/freevxfs/freevxfs.ko fs/freevxfs/freevxfs.o fs/freevxfs/freevxfs.mod.o;  true
