cmd_drivers/hid/hid-nti.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/hid/hid-nti.ko drivers/hid/hid-nti.o drivers/hid/hid-nti.mod.o;  true
