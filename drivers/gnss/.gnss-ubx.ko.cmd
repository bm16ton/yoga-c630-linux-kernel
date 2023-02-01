cmd_drivers/gnss/gnss-ubx.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/gnss/gnss-ubx.ko drivers/gnss/gnss-ubx.o drivers/gnss/gnss-ubx.mod.o;  true
