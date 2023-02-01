cmd_fs/fscache/fscache.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o fs/fscache/fscache.ko fs/fscache/fscache.o fs/fscache/fscache.mod.o;  true
