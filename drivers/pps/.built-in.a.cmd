cmd_drivers/pps/built-in.a := rm -f drivers/pps/built-in.a;  printf "drivers/pps/%s " pps.o kapi.o sysfs.o clients/built-in.a generators/built-in.a | xargs ar cDPrST drivers/pps/built-in.a
