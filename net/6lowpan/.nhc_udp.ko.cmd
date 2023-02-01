cmd_net/6lowpan/nhc_udp.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/6lowpan/nhc_udp.ko net/6lowpan/nhc_udp.o net/6lowpan/nhc_udp.mod.o;  true
