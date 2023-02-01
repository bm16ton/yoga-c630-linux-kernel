cmd_drivers/spi/built-in.a := rm -f drivers/spi/built-in.a;  printf "drivers/spi/%s " spi.o spi-mem.o spi-geni-qcom.o | xargs ar cDPrST drivers/spi/built-in.a
