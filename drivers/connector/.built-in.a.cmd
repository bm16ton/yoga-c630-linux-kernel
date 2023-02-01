cmd_drivers/connector/built-in.a := rm -f drivers/connector/built-in.a;  printf "drivers/connector/%s " cn_queue.o connector.o cn_proc.o | xargs ar cDPrST drivers/connector/built-in.a
