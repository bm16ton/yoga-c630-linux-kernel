cmd_net/sched/sch_mqprio.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/sched/sch_mqprio.ko net/sched/sch_mqprio.o net/sched/sch_mqprio.mod.o;  true
