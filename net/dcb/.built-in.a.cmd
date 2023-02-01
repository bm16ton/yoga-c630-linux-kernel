cmd_net/dcb/built-in.a := rm -f net/dcb/built-in.a;  printf "net/dcb/%s " dcbnl.o dcbevent.o | xargs ar cDPrST net/dcb/built-in.a
