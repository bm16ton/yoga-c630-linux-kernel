cmd_net/sched/sch_pie.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/sched/sch_pie.ko net/sched/sch_pie.o net/sched/sch_pie.mod.o;  true
