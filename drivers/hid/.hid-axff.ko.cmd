cmd_drivers/hid/hid-axff.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/hid/hid-axff.ko drivers/hid/hid-axff.o drivers/hid/hid-axff.mod.o;  true
