cmd_drivers/hid/hid-ite.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/hid/hid-ite.ko drivers/hid/hid-ite.o drivers/hid/hid-ite.mod.o;  true
