cmd_drivers/interconnect/built-in.a := rm -f drivers/interconnect/built-in.a;  printf "drivers/interconnect/%s " core.o bulk.o qcom/built-in.a | xargs ar cDPrST drivers/interconnect/built-in.a
