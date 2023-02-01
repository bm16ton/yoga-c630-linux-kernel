cmd_drivers/bus/mhi/built-in.a := rm -f drivers/bus/mhi/built-in.a;  printf "drivers/bus/mhi/%s " host/built-in.a ep/built-in.a | xargs ar cDPrST drivers/bus/mhi/built-in.a
