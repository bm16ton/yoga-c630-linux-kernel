cmd_drivers/char/ppdev.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/char/ppdev.ko drivers/char/ppdev.o drivers/char/ppdev.mod.o;  true
