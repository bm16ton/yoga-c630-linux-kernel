cmd_net/key/af_key.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/key/af_key.ko net/key/af_key.o net/key/af_key.mod.o;  true
