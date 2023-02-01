cmd_drivers/usb/serial/built-in.a := rm -f drivers/usb/serial/built-in.a;  printf "drivers/usb/serial/%s " usb-serial.o generic.o bus.o console.o | xargs ar cDPrST drivers/usb/serial/built-in.a
