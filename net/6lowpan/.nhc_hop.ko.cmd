cmd_net/6lowpan/nhc_hop.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/6lowpan/nhc_hop.ko net/6lowpan/nhc_hop.o net/6lowpan/nhc_hop.mod.o;  true
