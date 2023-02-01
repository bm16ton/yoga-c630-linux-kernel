cmd_net/bpf/built-in.a := rm -f net/bpf/built-in.a;  printf "net/bpf/%s " test_run.o bpf_dummy_struct_ops.o | xargs ar cDPrST net/bpf/built-in.a
