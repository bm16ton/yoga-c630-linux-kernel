cmd_net/netfilter/xt_sctp.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/netfilter/xt_sctp.ko net/netfilter/xt_sctp.o net/netfilter/xt_sctp.mod.o;  true
