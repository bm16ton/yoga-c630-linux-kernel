cmd_net/can/can-gw.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/can/can-gw.ko net/can/can-gw.o net/can/can-gw.mod.o;  true
