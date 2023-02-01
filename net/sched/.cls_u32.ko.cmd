cmd_net/sched/cls_u32.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/sched/cls_u32.ko net/sched/cls_u32.o net/sched/cls_u32.mod.o;  true
