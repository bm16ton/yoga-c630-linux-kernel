cmd_drivers/hid/hid-rmi.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/hid/hid-rmi.ko drivers/hid/hid-rmi.o drivers/hid/hid-rmi.mod.o;  true
