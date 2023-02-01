cmd_net/sched/sch_plug.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/sched/sch_plug.ko net/sched/sch_plug.o net/sched/sch_plug.mod.o;  true
