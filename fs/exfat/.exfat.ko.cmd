cmd_fs/exfat/exfat.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o fs/exfat/exfat.ko fs/exfat/exfat.o fs/exfat/exfat.mod.o;  true
