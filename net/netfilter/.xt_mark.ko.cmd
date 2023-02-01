cmd_net/netfilter/xt_mark.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/netfilter/xt_mark.ko net/netfilter/xt_mark.o net/netfilter/xt_mark.mod.o;  true
