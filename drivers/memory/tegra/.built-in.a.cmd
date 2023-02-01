cmd_drivers/memory/tegra/built-in.a := rm -f drivers/memory/tegra/built-in.a;  printf "drivers/memory/tegra/%s " mc.o tegra124.o tegra210.o | xargs ar cDPrST drivers/memory/tegra/built-in.a
