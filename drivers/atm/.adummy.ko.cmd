cmd_drivers/atm/adummy.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/atm/adummy.ko drivers/atm/adummy.o drivers/atm/adummy.mod.o;  true
