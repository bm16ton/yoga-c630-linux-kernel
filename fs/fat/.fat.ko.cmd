cmd_fs/fat/fat.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o fs/fat/fat.ko fs/fat/fat.o fs/fat/fat.mod.o;  true
