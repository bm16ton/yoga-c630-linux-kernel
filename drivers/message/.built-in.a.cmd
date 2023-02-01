cmd_drivers/message/built-in.a := rm -f drivers/message/built-in.a;  printf "drivers/message/%s " fusion/built-in.a | xargs ar cDPrST drivers/message/built-in.a
