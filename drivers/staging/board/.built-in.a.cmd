cmd_drivers/staging/board/built-in.a := rm -f drivers/staging/board/built-in.a;  printf "drivers/staging/board/%s " board.o | xargs ar cDPrST drivers/staging/board/built-in.a
