cmd_net/sched/em_meta.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/sched/em_meta.ko net/sched/em_meta.o net/sched/em_meta.mod.o;  true
