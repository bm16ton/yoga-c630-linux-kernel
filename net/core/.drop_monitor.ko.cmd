cmd_net/core/drop_monitor.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/core/drop_monitor.ko net/core/drop_monitor.o net/core/drop_monitor.mod.o;  true
