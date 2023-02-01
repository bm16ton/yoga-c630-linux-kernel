cmd_net/atm/lec.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/atm/lec.ko net/atm/lec.o net/atm/lec.mod.o;  true
