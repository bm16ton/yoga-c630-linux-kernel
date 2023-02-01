cmd_net/9p/9pnet_fd.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/9p/9pnet_fd.ko net/9p/9pnet_fd.o net/9p/9pnet_fd.mod.o;  true
