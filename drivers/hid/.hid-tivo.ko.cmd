cmd_drivers/hid/hid-tivo.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/hid/hid-tivo.ko drivers/hid/hid-tivo.o drivers/hid/hid-tivo.mod.o;  true
