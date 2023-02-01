cmd_fs/romfs/romfs.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o fs/romfs/romfs.ko fs/romfs/romfs.o fs/romfs/romfs.mod.o;  true
