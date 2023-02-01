cmd_drivers/hwmon/sht3x.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/hwmon/sht3x.ko drivers/hwmon/sht3x.o drivers/hwmon/sht3x.mod.o;  true
