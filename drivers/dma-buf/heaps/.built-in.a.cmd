cmd_drivers/dma-buf/heaps/built-in.a := rm -f drivers/dma-buf/heaps/built-in.a;  printf "drivers/dma-buf/heaps/%s " system_heap.o cma_heap.o | xargs ar cDPrST drivers/dma-buf/heaps/built-in.a
