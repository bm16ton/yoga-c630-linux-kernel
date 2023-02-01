cmd_net/netrom/netrom.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/netrom/netrom.ko net/netrom/netrom.o net/netrom/netrom.mod.o;  true
