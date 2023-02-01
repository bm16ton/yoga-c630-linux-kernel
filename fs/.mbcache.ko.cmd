cmd_fs/mbcache.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o fs/mbcache.ko fs/mbcache.o fs/mbcache.mod.o;  true
