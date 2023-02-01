cmd_net/strparser/built-in.a := rm -f net/strparser/built-in.a;  printf "net/strparser/%s " strparser.o | xargs ar cDPrST net/strparser/built-in.a
