cmd_net/sched/sch_netem.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/sched/sch_netem.ko net/sched/sch_netem.o net/sched/sch_netem.mod.o;  true
