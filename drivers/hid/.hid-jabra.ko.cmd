cmd_drivers/hid/hid-jabra.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/hid/hid-jabra.ko drivers/hid/hid-jabra.o drivers/hid/hid-jabra.mod.o;  true
