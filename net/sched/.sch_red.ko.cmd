cmd_net/sched/sch_red.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/sched/sch_red.ko net/sched/sch_red.o net/sched/sch_red.mod.o;  true
