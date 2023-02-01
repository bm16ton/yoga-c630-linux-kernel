cmd_net/ipv4/tcp_dctcp.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/ipv4/tcp_dctcp.ko net/ipv4/tcp_dctcp.o net/ipv4/tcp_dctcp.mod.o;  true
