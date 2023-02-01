cmd_net/rds/rds.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/rds/rds.ko net/rds/rds.o net/rds/rds.mod.o;  true
