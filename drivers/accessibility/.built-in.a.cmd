cmd_drivers/accessibility/built-in.a := rm -f drivers/accessibility/built-in.a;  printf "drivers/accessibility/%s " braille/built-in.a | xargs ar cDPrST drivers/accessibility/built-in.a
