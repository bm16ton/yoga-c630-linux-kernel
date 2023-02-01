cmd_drivers/hid/hid-gfrm.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/hid/hid-gfrm.ko drivers/hid/hid-gfrm.o drivers/hid/hid-gfrm.mod.o;  true
