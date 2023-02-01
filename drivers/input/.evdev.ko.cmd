cmd_drivers/input/evdev.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/input/evdev.ko drivers/input/evdev.o drivers/input/evdev.mod.o;  true
