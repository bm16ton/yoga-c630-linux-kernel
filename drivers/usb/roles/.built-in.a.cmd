cmd_drivers/usb/roles/built-in.a := rm -f drivers/usb/roles/built-in.a;  printf "drivers/usb/roles/%s " class.o | xargs ar cDPrST drivers/usb/roles/built-in.a
