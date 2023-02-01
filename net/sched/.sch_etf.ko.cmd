cmd_net/sched/sch_etf.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/sched/sch_etf.ko net/sched/sch_etf.o net/sched/sch_etf.mod.o;  true
