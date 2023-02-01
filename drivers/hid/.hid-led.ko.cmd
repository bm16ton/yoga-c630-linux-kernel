cmd_drivers/hid/hid-led.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/hid/hid-led.ko drivers/hid/hid-led.o drivers/hid/hid-led.mod.o;  true
