cmd_drivers/hid/hid-sjoy.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/hid/hid-sjoy.ko drivers/hid/hid-sjoy.o drivers/hid/hid-sjoy.mod.o;  true
