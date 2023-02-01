cmd_net/xdp/built-in.a := rm -f net/xdp/built-in.a;  printf "net/xdp/%s " xsk.o xdp_umem.o xsk_queue.o xskmap.o xsk_buff_pool.o | xargs ar cDPrST net/xdp/built-in.a
