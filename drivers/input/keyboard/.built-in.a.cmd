cmd_drivers/input/keyboard/built-in.a := rm -f drivers/input/keyboard/built-in.a;  printf "drivers/input/keyboard/%s " atkbd.o | xargs ar cDPrST drivers/input/keyboard/built-in.a
