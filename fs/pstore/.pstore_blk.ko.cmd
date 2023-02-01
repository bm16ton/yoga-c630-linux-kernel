cmd_fs/pstore/pstore_blk.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o fs/pstore/pstore_blk.ko fs/pstore/pstore_blk.o fs/pstore/pstore_blk.mod.o;  true
