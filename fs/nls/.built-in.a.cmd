cmd_fs/nls/built-in.a := rm -f fs/nls/built-in.a;  printf "fs/nls/%s " nls_base.o | xargs ar cDPrST fs/nls/built-in.a
