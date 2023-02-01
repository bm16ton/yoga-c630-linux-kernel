cmd_net/sched/sch_cbs.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/sched/sch_cbs.ko net/sched/sch_cbs.o net/sched/sch_cbs.mod.o;  true
