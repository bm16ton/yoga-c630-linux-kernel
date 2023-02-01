cmd_drivers/rtc/rtc-rk808.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/rtc/rtc-rk808.ko drivers/rtc/rtc-rk808.o drivers/rtc/rtc-rk808.mod.o;  true
