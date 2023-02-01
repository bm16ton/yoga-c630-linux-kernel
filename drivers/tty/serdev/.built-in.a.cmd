cmd_drivers/tty/serdev/built-in.a := rm -f drivers/tty/serdev/built-in.a;  printf "drivers/tty/serdev/%s " core.o serdev-ttyport.o | xargs ar cDPrST drivers/tty/serdev/built-in.a
