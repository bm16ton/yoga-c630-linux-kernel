cmd_fs/nfs_common/nfs_acl.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o fs/nfs_common/nfs_acl.ko fs/nfs_common/nfs_acl.o fs/nfs_common/nfs_acl.mod.o;  true
