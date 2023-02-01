cmd_drivers/net/usb/asix.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/net/usb/asix.ko drivers/net/usb/asix.o drivers/net/usb/asix.mod.o;  true
