cmd_net/sched/em_cmp.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/sched/em_cmp.ko net/sched/em_cmp.o net/sched/em_cmp.mod.o;  true
