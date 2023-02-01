cmd_drivers/misc/fastrpc.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/misc/fastrpc.ko drivers/misc/fastrpc.o drivers/misc/fastrpc.mod.o;  true
