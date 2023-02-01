cmd_net/sched/em_canid.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/sched/em_canid.ko net/sched/em_canid.o net/sched/em_canid.mod.o;  true
