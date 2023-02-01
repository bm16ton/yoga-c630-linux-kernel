cmd_net/netfilter/xt_time.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/netfilter/xt_time.ko net/netfilter/xt_time.o net/netfilter/xt_time.mod.o;  true
