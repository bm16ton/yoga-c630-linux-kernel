cmd_net/mpls/built-in.a := rm -f net/mpls/built-in.a;  printf "net/mpls/%s " mpls_gso.o | xargs ar cDPrST net/mpls/built-in.a
