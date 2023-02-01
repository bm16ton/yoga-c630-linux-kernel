cmd_drivers/misc/tsl2550.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/misc/tsl2550.ko drivers/misc/tsl2550.o drivers/misc/tsl2550.mod.o;  true
