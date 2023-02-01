cmd_net/netfilter/nft_ct.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/netfilter/nft_ct.ko net/netfilter/nft_ct.o net/netfilter/nft_ct.mod.o;  true
