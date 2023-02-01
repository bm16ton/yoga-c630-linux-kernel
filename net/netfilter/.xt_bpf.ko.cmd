cmd_net/netfilter/xt_bpf.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/netfilter/xt_bpf.ko net/netfilter/xt_bpf.o net/netfilter/xt_bpf.mod.o;  true
