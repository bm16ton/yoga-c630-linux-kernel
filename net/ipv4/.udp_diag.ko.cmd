cmd_net/ipv4/udp_diag.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/ipv4/udp_diag.ko net/ipv4/udp_diag.o net/ipv4/udp_diag.mod.o;  true
