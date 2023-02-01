cmd_drivers/firmware/xilinx/built-in.a := rm -f drivers/firmware/xilinx/built-in.a;  printf "drivers/firmware/xilinx/%s " zynqmp.o | xargs ar cDPrST drivers/firmware/xilinx/built-in.a
