cmd_drivers/hid/hid-elo.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/hid/hid-elo.ko drivers/hid/hid-elo.o drivers/hid/hid-elo.mod.o;  true
