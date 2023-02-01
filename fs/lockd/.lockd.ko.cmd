cmd_fs/lockd/lockd.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o fs/lockd/lockd.ko fs/lockd/lockd.o fs/lockd/lockd.mod.o;  true
