cmd_fs/pstore/pstore_zone.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o fs/pstore/pstore_zone.ko fs/pstore/pstore_zone.o fs/pstore/pstore_zone.mod.o;  true
