cmd_drivers/net/usb/catc.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/net/usb/catc.ko drivers/net/usb/catc.o drivers/net/usb/catc.mod.o;  true
