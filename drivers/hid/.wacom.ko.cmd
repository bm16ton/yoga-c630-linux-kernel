cmd_drivers/hid/wacom.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/hid/wacom.ko drivers/hid/wacom.o drivers/hid/wacom.mod.o;  true
