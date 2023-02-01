cmd_net/sched/sch_tbf.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/sched/sch_tbf.ko net/sched/sch_tbf.o net/sched/sch_tbf.mod.o;  true
