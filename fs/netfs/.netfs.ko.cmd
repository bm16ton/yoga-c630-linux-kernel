cmd_fs/netfs/netfs.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o fs/netfs/netfs.ko fs/netfs/netfs.o fs/netfs/netfs.mod.o;  true
