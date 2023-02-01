cmd_net/netfilter/xt_hl.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/netfilter/xt_hl.ko net/netfilter/xt_hl.o net/netfilter/xt_hl.mod.o;  true
