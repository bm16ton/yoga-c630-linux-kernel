cmd_fs/ext4/ext4.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o fs/ext4/ext4.ko fs/ext4/ext4.o fs/ext4/ext4.mod.o;  true
