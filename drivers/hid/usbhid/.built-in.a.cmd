cmd_drivers/hid/usbhid/built-in.a := rm -f drivers/hid/usbhid/built-in.a;  printf "drivers/hid/usbhid/%s " hid-core.o hiddev.o hid-pidff.o | xargs ar cDPrST drivers/hid/usbhid/built-in.a
