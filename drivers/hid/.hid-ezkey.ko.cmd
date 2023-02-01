cmd_drivers/hid/hid-ezkey.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/hid/hid-ezkey.ko drivers/hid/hid-ezkey.o drivers/hid/hid-ezkey.mod.o;  true
