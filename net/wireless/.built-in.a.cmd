cmd_net/wireless/built-in.a := rm -f net/wireless/built-in.a;  printf "net/wireless/%s " wext-core.o wext-proc.o wext-spy.o wext-priv.o | xargs ar cDPrST net/wireless/built-in.a
