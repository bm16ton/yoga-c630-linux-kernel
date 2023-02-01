cmd_drivers/soc/rockchip/built-in.a := rm -f drivers/soc/rockchip/built-in.a;  printf "drivers/soc/rockchip/%s " grf.o pm_domains.o | xargs ar cDPrST drivers/soc/rockchip/built-in.a
