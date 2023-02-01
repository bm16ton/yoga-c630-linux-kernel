cmd_drivers/net/ethernet/dec/built-in.a := rm -f drivers/net/ethernet/dec/built-in.a;  printf "drivers/net/ethernet/dec/%s " tulip/built-in.a | xargs ar cDPrST drivers/net/ethernet/dec/built-in.a
