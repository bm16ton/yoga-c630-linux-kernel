cmd_drivers/tee/tee.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/tee/tee.ko drivers/tee/tee.o drivers/tee/tee.mod.o;  true
