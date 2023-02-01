cmd_drivers/net/wireless/ti/built-in.a := rm -f drivers/net/wireless/ti/built-in.a;  printf "drivers/net/wireless/ti/%s " wilink_platform_data.o | xargs ar cDPrST drivers/net/wireless/ti/built-in.a
