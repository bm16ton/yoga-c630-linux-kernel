cmd_drivers/net/mhi_net.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/net/mhi_net.ko drivers/net/mhi_net.o drivers/net/mhi_net.mod.o;  true
