cmd_net/smc/smc_diag.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/smc/smc_diag.ko net/smc/smc_diag.o net/smc/smc_diag.mod.o;  true
