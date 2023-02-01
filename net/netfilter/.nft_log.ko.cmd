cmd_net/netfilter/nft_log.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/netfilter/nft_log.ko net/netfilter/nft_log.o net/netfilter/nft_log.mod.o;  true
