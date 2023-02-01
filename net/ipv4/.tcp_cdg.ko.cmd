cmd_net/ipv4/tcp_cdg.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/ipv4/tcp_cdg.ko net/ipv4/tcp_cdg.o net/ipv4/tcp_cdg.mod.o;  true
