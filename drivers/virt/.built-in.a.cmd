cmd_drivers/virt/built-in.a := rm -f drivers/virt/built-in.a;  printf "drivers/virt/%s " vmgenid.o vboxguest/built-in.a | xargs ar cDPrST drivers/virt/built-in.a
