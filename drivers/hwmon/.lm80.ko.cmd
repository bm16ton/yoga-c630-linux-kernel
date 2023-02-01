cmd_drivers/hwmon/lm80.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/hwmon/lm80.ko drivers/hwmon/lm80.o drivers/hwmon/lm80.mod.o;  true
