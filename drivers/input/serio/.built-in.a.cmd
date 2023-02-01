cmd_drivers/input/serio/built-in.a := rm -f drivers/input/serio/built-in.a;  printf "drivers/input/serio/%s " serio.o serport.o libps2.o | xargs ar cDPrST drivers/input/serio/built-in.a
