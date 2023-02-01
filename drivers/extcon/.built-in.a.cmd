cmd_drivers/extcon/built-in.a := rm -f drivers/extcon/built-in.a;  printf "drivers/extcon/%s " extcon.o devres.o | xargs ar cDPrST drivers/extcon/built-in.a
