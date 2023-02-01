cmd_fs/nfs/nfsv3.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o fs/nfs/nfsv3.ko fs/nfs/nfsv3.o fs/nfs/nfsv3.mod.o;  true
