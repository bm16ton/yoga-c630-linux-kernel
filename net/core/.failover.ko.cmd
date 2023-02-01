cmd_net/core/failover.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/core/failover.ko net/core/failover.o net/core/failover.mod.o;  true
