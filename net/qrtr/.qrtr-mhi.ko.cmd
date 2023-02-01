cmd_net/qrtr/qrtr-mhi.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/qrtr/qrtr-mhi.ko net/qrtr/qrtr-mhi.o net/qrtr/qrtr-mhi.mod.o;  true
