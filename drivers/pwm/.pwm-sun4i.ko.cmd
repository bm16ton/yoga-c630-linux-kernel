cmd_drivers/pwm/pwm-sun4i.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/pwm/pwm-sun4i.ko drivers/pwm/pwm-sun4i.o drivers/pwm/pwm-sun4i.mod.o;  true
