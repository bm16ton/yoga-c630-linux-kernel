cmd_net/9p/9pnet_virtio.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/9p/9pnet_virtio.ko net/9p/9pnet_virtio.o net/9p/9pnet_virtio.mod.o;  true
