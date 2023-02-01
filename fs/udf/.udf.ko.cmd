cmd_fs/udf/udf.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o fs/udf/udf.ko fs/udf/udf.o fs/udf/udf.mod.o;  true
