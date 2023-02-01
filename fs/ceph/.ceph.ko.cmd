cmd_fs/ceph/ceph.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o fs/ceph/ceph.ko fs/ceph/ceph.o fs/ceph/ceph.mod.o;  true
