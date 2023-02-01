cmd_net/sched/em_text.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/sched/em_text.ko net/sched/em_text.o net/sched/em_text.mod.o;  true
