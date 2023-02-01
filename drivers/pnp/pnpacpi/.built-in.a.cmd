cmd_drivers/pnp/pnpacpi/built-in.a := rm -f drivers/pnp/pnpacpi/built-in.a;  printf "drivers/pnp/pnpacpi/%s " core.o rsparser.o | xargs ar cDPrST drivers/pnp/pnpacpi/built-in.a
