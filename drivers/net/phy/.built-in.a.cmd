cmd_drivers/net/phy/built-in.a := rm -f drivers/net/phy/built-in.a;  printf "drivers/net/phy/%s " mdio-boardinfo.o sfp-bus.o | xargs ar cDPrST drivers/net/phy/built-in.a
