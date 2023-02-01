cmd_net/xfrm/xfrm_algo.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/xfrm/xfrm_algo.ko net/xfrm/xfrm_algo.o net/xfrm/xfrm_algo.mod.o;  true
