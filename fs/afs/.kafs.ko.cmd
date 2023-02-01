cmd_fs/afs/kafs.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o fs/afs/kafs.ko fs/afs/kafs.o fs/afs/kafs.mod.o;  true
