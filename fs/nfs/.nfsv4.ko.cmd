cmd_fs/nfs/nfsv4.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o fs/nfs/nfsv4.ko fs/nfs/nfsv4.o fs/nfs/nfsv4.mod.o;  true
