cmd_net/ipv6/esp6_offload.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/ipv6/esp6_offload.ko net/ipv6/esp6_offload.o net/ipv6/esp6_offload.mod.o;  true
