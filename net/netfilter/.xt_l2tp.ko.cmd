cmd_net/netfilter/xt_l2tp.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/netfilter/xt_l2tp.ko net/netfilter/xt_l2tp.o net/netfilter/xt_l2tp.mod.o;  true
