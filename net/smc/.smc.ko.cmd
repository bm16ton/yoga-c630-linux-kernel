cmd_net/smc/smc.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/smc/smc.ko net/smc/smc.o net/smc/smc.mod.o;  true
