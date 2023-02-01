cmd_net/atm/atm.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/atm/atm.ko net/atm/atm.o net/atm/atm.mod.o;  true
