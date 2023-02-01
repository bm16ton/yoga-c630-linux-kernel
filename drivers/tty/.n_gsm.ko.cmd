cmd_drivers/tty/n_gsm.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/tty/n_gsm.ko drivers/tty/n_gsm.o drivers/tty/n_gsm.mod.o;  true
