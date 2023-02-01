cmd_arch/arm64/net/built-in.a := rm -f arch/arm64/net/built-in.a;  printf "arch/arm64/net/%s " bpf_jit_comp.o | xargs ar cDPrST arch/arm64/net/built-in.a
