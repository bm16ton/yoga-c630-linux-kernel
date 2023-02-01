cmd_net/rds/rds_rdma.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/rds/rds_rdma.ko net/rds/rds_rdma.o net/rds/rds_rdma.mod.o;  true
