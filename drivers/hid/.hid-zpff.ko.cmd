cmd_drivers/hid/hid-zpff.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/hid/hid-zpff.ko drivers/hid/hid-zpff.o drivers/hid/hid-zpff.mod.o;  true
