cmd_drivers/hid/hid-apple.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/hid/hid-apple.ko drivers/hid/hid-apple.o drivers/hid/hid-apple.mod.o;  true
