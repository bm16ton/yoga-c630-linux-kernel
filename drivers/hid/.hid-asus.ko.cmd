cmd_drivers/hid/hid-asus.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/hid/hid-asus.ko drivers/hid/hid-asus.o drivers/hid/hid-asus.mod.o;  true
