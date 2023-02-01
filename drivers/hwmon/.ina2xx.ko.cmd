cmd_drivers/hwmon/ina2xx.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/hwmon/ina2xx.ko drivers/hwmon/ina2xx.o drivers/hwmon/ina2xx.mod.o;  true
