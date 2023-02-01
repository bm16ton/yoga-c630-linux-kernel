cmd_drivers/hid/hid-xinmo.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/hid/hid-xinmo.ko drivers/hid/hid-xinmo.o drivers/hid/hid-xinmo.mod.o;  true
