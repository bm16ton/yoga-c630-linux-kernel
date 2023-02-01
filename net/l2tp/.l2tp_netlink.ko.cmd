cmd_net/l2tp/l2tp_netlink.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/l2tp/l2tp_netlink.ko net/l2tp/l2tp_netlink.o net/l2tp/l2tp_netlink.mod.o;  true
