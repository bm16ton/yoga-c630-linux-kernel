cmd_drivers/hwmon/sht21.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/hwmon/sht21.ko drivers/hwmon/sht21.o drivers/hwmon/sht21.mod.o;  true
