cmd_drivers/hwmon/ina3221.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/hwmon/ina3221.ko drivers/hwmon/ina3221.o drivers/hwmon/ina3221.mod.o;  true
