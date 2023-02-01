cmd_drivers/leds/uleds.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/leds/uleds.ko drivers/leds/uleds.o drivers/leds/uleds.mod.o;  true
