cmd_drivers/spmi/built-in.a := rm -f drivers/spmi/built-in.a;  printf "drivers/spmi/%s " spmi.o spmi-pmic-arb.o | xargs ar cDPrST drivers/spmi/built-in.a
