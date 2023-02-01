cmd_drivers/leds/leds-pwm.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/leds/leds-pwm.ko drivers/leds/leds-pwm.o drivers/leds/leds-pwm.mod.o;  true
