cmd_net/9p/9pnet_xen.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/9p/9pnet_xen.ko net/9p/9pnet_xen.o net/9p/9pnet_xen.mod.o;  true
