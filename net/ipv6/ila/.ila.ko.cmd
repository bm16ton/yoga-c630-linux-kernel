cmd_net/ipv6/ila/ila.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/ipv6/ila/ila.ko net/ipv6/ila/ila.o net/ipv6/ila/ila.mod.o;  true
