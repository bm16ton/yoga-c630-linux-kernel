cmd_net/netfilter/xt_LED.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/netfilter/xt_LED.ko net/netfilter/xt_LED.o net/netfilter/xt_LED.mod.o;  true
