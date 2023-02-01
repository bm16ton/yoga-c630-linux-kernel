cmd_drivers/hwmon/sht4x.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/hwmon/sht4x.ko drivers/hwmon/sht4x.o drivers/hwmon/sht4x.mod.o;  true
