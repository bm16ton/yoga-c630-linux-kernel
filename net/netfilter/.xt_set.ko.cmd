cmd_net/netfilter/xt_set.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/netfilter/xt_set.ko net/netfilter/xt_set.o net/netfilter/xt_set.mod.o;  true
