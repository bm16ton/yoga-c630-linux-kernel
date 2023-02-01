cmd_fs/romfs/romfs.o := ld  -EL  -maarch64elf -z noexecstack     -r -o fs/romfs/romfs.o @fs/romfs/romfs.mod 
