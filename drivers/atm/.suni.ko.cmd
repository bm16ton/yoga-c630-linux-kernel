cmd_drivers/atm/suni.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/atm/suni.ko drivers/atm/suni.o drivers/atm/suni.mod.o;  true
