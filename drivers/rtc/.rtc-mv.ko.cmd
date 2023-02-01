cmd_drivers/rtc/rtc-mv.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/rtc/rtc-mv.ko drivers/rtc/rtc-mv.o drivers/rtc/rtc-mv.mod.o;  true
