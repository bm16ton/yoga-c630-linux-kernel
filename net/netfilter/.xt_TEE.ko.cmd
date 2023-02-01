cmd_net/netfilter/xt_TEE.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/netfilter/xt_TEE.ko net/netfilter/xt_TEE.o net/netfilter/xt_TEE.mod.o;  true
