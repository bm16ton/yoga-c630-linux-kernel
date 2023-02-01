cmd_drivers/gnss/gnss.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/gnss/gnss.ko drivers/gnss/gnss.o drivers/gnss/gnss.mod.o;  true
