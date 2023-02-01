cmd_drivers/hid/hid-topre.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/hid/hid-topre.ko drivers/hid/hid-topre.o drivers/hid/hid-topre.mod.o;  true
