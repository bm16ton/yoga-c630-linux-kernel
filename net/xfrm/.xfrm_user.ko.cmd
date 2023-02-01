cmd_net/xfrm/xfrm_user.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/xfrm/xfrm_user.ko net/xfrm/xfrm_user.o net/xfrm/xfrm_user.mod.o;  true
