cmd_drivers/atm/idt77105.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/atm/idt77105.ko drivers/atm/idt77105.o drivers/atm/idt77105.mod.o;  true
