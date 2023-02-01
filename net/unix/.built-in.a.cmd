cmd_net/unix/built-in.a := rm -f net/unix/built-in.a;  printf "net/unix/%s " af_unix.o garbage.o sysctl_net_unix.o unix_bpf.o scm.o | xargs ar cDPrST net/unix/built-in.a
