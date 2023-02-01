cmd_net/sched/act_ipt.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/sched/act_ipt.ko net/sched/act_ipt.o net/sched/act_ipt.mod.o;  true
