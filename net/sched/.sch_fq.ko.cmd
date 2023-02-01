cmd_net/sched/sch_fq.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/sched/sch_fq.ko net/sched/sch_fq.o net/sched/sch_fq.mod.o;  true
