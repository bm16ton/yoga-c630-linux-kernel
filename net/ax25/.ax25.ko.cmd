cmd_net/ax25/ax25.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/ax25/ax25.ko net/ax25/ax25.o net/ax25/ax25.mod.o;  true
