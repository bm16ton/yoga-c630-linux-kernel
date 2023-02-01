cmd_net/core/pktgen.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/core/pktgen.ko net/core/pktgen.o net/core/pktgen.mod.o;  true
