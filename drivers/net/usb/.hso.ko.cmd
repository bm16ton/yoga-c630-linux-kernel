cmd_drivers/net/usb/hso.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/net/usb/hso.ko drivers/net/usb/hso.o drivers/net/usb/hso.mod.o;  true
