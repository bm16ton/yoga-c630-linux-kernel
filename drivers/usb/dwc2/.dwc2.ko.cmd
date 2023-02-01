cmd_drivers/usb/dwc2/dwc2.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/usb/dwc2/dwc2.ko drivers/usb/dwc2/dwc2.o drivers/usb/dwc2/dwc2.mod.o;  true
