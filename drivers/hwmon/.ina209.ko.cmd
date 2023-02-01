cmd_drivers/hwmon/ina209.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/hwmon/ina209.ko drivers/hwmon/ina209.o drivers/hwmon/ina209.mod.o;  true
