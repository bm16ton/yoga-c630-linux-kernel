cmd_fs/ufs/ufs.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o fs/ufs/ufs.ko fs/ufs/ufs.o fs/ufs/ufs.mod.o;  true
