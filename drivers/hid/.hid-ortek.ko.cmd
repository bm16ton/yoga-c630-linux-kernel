cmd_drivers/hid/hid-ortek.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/hid/hid-ortek.ko drivers/hid/hid-ortek.o drivers/hid/hid-ortek.mod.o;  true
