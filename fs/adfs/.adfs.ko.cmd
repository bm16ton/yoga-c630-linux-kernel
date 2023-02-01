cmd_fs/adfs/adfs.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o fs/adfs/adfs.ko fs/adfs/adfs.o fs/adfs/adfs.mod.o;  true
