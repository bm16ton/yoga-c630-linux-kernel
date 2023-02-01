cmd_drivers/hid/hid-elan.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/hid/hid-elan.ko drivers/hid/hid-elan.o drivers/hid/hid-elan.mod.o;  true
