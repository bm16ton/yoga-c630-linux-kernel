cmd_net/sched/sch_codel.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/sched/sch_codel.ko net/sched/sch_codel.o net/sched/sch_codel.mod.o;  true
