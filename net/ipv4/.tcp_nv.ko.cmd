cmd_net/ipv4/tcp_nv.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/ipv4/tcp_nv.ko net/ipv4/tcp_nv.o net/ipv4/tcp_nv.mod.o;  true
