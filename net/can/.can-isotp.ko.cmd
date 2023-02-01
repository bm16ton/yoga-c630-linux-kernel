cmd_net/can/can-isotp.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/can/can-isotp.ko net/can/can-isotp.o net/can/can-isotp.mod.o;  true
