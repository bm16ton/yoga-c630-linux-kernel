cmd_net/l2tp/l2tp_core.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/l2tp/l2tp_core.ko net/l2tp/l2tp_core.o net/l2tp/l2tp_core.mod.o;  true
