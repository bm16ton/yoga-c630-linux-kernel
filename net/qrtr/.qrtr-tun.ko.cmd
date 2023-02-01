cmd_net/qrtr/qrtr-tun.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/qrtr/qrtr-tun.ko net/qrtr/qrtr-tun.o net/qrtr/qrtr-tun.mod.o;  true
