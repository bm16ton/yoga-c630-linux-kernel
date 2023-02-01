cmd_fs/coda/coda.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o fs/coda/coda.ko fs/coda/coda.o fs/coda/coda.mod.o;  true
