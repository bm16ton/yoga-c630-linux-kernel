cmd_drivers/hwmon/w83781d.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/hwmon/w83781d.ko drivers/hwmon/w83781d.o drivers/hwmon/w83781d.mod.o;  true
