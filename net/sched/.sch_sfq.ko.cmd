cmd_net/sched/sch_sfq.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/sched/sch_sfq.ko net/sched/sch_sfq.o net/sched/sch_sfq.mod.o;  true
