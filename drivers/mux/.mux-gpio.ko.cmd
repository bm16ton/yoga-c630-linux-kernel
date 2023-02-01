cmd_drivers/mux/mux-gpio.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/mux/mux-gpio.ko drivers/mux/mux-gpio.o drivers/mux/mux-gpio.mod.o;  true
