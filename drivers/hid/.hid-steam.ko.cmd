cmd_drivers/hid/hid-steam.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/hid/hid-steam.ko drivers/hid/hid-steam.o drivers/hid/hid-steam.mod.o;  true
