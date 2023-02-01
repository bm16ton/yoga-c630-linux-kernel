cmd_drivers/video/console/built-in.a := rm -f drivers/video/console/built-in.a;  printf "drivers/video/console/%s " dummycon.o | xargs ar cDPrST drivers/video/console/built-in.a
