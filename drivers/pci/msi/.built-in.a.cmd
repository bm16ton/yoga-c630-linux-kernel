cmd_drivers/pci/msi/built-in.a := rm -f drivers/pci/msi/built-in.a;  printf "drivers/pci/msi/%s " pcidev_msi.o msi.o irqdomain.o | xargs ar cDPrST drivers/pci/msi/built-in.a
