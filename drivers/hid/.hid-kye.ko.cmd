cmd_drivers/hid/hid-kye.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/hid/hid-kye.ko drivers/hid/hid-kye.o drivers/hid/hid-kye.mod.o;  true
