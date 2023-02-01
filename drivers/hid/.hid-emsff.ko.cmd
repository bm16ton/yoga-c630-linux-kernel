cmd_drivers/hid/hid-emsff.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/hid/hid-emsff.ko drivers/hid/hid-emsff.o drivers/hid/hid-emsff.mod.o;  true
