cmd_net/tipc/diag.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/tipc/diag.ko net/tipc/diag.o net/tipc/diag.mod.o;  true
