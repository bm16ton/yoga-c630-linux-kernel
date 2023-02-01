cmd_drivers/video/backlight/built-in.a := rm -f drivers/video/backlight/built-in.a;  printf "drivers/video/backlight/%s " backlight.o | xargs ar cDPrST drivers/video/backlight/built-in.a
