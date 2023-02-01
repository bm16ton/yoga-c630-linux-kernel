cmd_drivers/hid/hid-gaff.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/hid/hid-gaff.ko drivers/hid/hid-gaff.o drivers/hid/hid-gaff.mod.o;  true
