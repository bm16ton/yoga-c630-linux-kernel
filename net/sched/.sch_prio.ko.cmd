cmd_net/sched/sch_prio.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/sched/sch_prio.ko net/sched/sch_prio.o net/sched/sch_prio.mod.o;  true
