cmd_drivers/platform/built-in.a := rm -f drivers/platform/built-in.a;  printf "drivers/platform/%s " chrome/built-in.a surface/built-in.a | xargs ar cDPrST drivers/platform/built-in.a
