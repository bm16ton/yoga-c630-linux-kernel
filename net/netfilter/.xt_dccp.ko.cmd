cmd_net/netfilter/xt_dccp.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/netfilter/xt_dccp.ko net/netfilter/xt_dccp.o net/netfilter/xt_dccp.mod.o;  true
