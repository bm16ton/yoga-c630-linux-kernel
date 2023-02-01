cmd_net/sched/sch_cbq.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/sched/sch_cbq.ko net/sched/sch_cbq.o net/sched/sch_cbq.mod.o;  true
