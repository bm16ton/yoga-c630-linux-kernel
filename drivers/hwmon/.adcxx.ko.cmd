cmd_drivers/hwmon/adcxx.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/hwmon/adcxx.ko drivers/hwmon/adcxx.o drivers/hwmon/adcxx.mod.o;  true
