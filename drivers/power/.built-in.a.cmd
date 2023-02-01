cmd_drivers/power/built-in.a := rm -f drivers/power/built-in.a;  printf "drivers/power/%s " reset/built-in.a supply/built-in.a | xargs ar cDPrST drivers/power/built-in.a
