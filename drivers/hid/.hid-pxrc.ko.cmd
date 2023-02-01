cmd_drivers/hid/hid-pxrc.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/hid/hid-pxrc.ko drivers/hid/hid-pxrc.o drivers/hid/hid-pxrc.mod.o;  true
