cmd_drivers/hid/hid-tmff.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/hid/hid-tmff.ko drivers/hid/hid-tmff.o drivers/hid/hid-tmff.mod.o;  true
