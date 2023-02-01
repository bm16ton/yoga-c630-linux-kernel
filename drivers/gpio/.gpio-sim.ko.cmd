cmd_drivers/gpio/gpio-sim.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/gpio/gpio-sim.ko drivers/gpio/gpio-sim.o drivers/gpio/gpio-sim.mod.o;  true
