cmd_drivers/hid/hid-icade.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/hid/hid-icade.ko drivers/hid/hid-icade.o drivers/hid/hid-icade.mod.o;  true
