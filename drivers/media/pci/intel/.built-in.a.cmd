cmd_drivers/media/pci/intel/built-in.a := rm -f drivers/media/pci/intel/built-in.a;  printf "drivers/media/pci/intel/%s " ipu3/built-in.a | xargs ar cDPrST drivers/media/pci/intel/built-in.a
