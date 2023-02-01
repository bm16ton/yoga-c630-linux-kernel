cmd_net/6lowpan/nhc_ipv6.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/6lowpan/nhc_ipv6.ko net/6lowpan/nhc_ipv6.o net/6lowpan/nhc_ipv6.mod.o;  true
