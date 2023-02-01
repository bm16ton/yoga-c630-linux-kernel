cmd_net/ipv6/esp6.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/ipv6/esp6.ko net/ipv6/esp6.o net/ipv6/esp6.mod.o;  true
