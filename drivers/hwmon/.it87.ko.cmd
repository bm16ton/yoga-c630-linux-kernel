cmd_drivers/hwmon/it87.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/hwmon/it87.ko drivers/hwmon/it87.o drivers/hwmon/it87.mod.o;  true
