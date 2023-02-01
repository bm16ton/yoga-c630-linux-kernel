cmd_net/l2tp/l2tp_eth.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/l2tp/l2tp_eth.ko net/l2tp/l2tp_eth.o net/l2tp/l2tp_eth.mod.o;  true
