cmd_net/mpls/mpls_router.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/mpls/mpls_router.ko net/mpls/mpls_router.o net/mpls/mpls_router.mod.o;  true
