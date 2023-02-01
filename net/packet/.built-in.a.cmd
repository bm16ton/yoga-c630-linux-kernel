cmd_net/packet/built-in.a := rm -f net/packet/built-in.a;  printf "net/packet/%s " af_packet.o | xargs ar cDPrST net/packet/built-in.a
