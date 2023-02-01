cmd_fs/qnx4/qnx4.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o fs/qnx4/qnx4.ko fs/qnx4/qnx4.o fs/qnx4/qnx4.mod.o;  true
