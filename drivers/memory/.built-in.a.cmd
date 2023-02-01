cmd_drivers/memory/built-in.a := rm -f drivers/memory/built-in.a;  printf "drivers/memory/%s " tegra/built-in.a | xargs ar cDPrST drivers/memory/built-in.a
