cmd_drivers/gpu/host1x/built-in.a := rm -f drivers/gpu/host1x/built-in.a;  printf "drivers/gpu/host1x/%s " context_bus.o | xargs ar cDPrST drivers/gpu/host1x/built-in.a
