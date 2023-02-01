cmd_drivers/atm/iphase.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/atm/iphase.ko drivers/atm/iphase.o drivers/atm/iphase.mod.o;  true
