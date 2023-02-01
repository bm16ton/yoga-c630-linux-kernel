cmd_net/netfilter/xt_cpu.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/netfilter/xt_cpu.ko net/netfilter/xt_cpu.o net/netfilter/xt_cpu.mod.o;  true
