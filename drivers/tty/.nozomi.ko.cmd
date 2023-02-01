cmd_drivers/tty/nozomi.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/tty/nozomi.ko drivers/tty/nozomi.o drivers/tty/nozomi.mod.o;  true
