cmd_fs/sysv/sysv.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o fs/sysv/sysv.ko fs/sysv/sysv.o fs/sysv/sysv.mod.o;  true
