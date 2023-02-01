cmd_fs/affs/affs.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o fs/affs/affs.ko fs/affs/affs.o fs/affs/affs.mod.o;  true
