cmd_drivers/hwmon/sht15.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/hwmon/sht15.ko drivers/hwmon/sht15.o drivers/hwmon/sht15.mod.o;  true
