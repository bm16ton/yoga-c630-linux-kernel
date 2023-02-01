cmd_net/9p/9pnet_rdma.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/9p/9pnet_rdma.ko net/9p/9pnet_rdma.o net/9p/9pnet_rdma.mod.o;  true
