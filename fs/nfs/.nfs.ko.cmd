cmd_fs/nfs/nfs.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o fs/nfs/nfs.ko fs/nfs/nfs.o fs/nfs/nfs.mod.o;  true
