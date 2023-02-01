cmd_net/atm/mpoa.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/atm/mpoa.ko net/atm/mpoa.o net/atm/mpoa.mod.o;  true
