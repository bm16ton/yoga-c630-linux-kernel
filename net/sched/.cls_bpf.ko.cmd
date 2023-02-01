cmd_net/sched/cls_bpf.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/sched/cls_bpf.ko net/sched/cls_bpf.o net/sched/cls_bpf.mod.o;  true
