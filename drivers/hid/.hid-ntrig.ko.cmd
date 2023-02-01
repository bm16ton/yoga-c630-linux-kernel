cmd_drivers/hid/hid-ntrig.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/hid/hid-ntrig.ko drivers/hid/hid-ntrig.o drivers/hid/hid-ntrig.mod.o;  true
