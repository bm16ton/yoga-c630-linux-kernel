cmd_drivers/hid/hid-sony.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/hid/hid-sony.ko drivers/hid/hid-sony.o drivers/hid/hid-sony.mod.o;  true
