cmd_fs/quota/built-in.a := rm -f fs/quota/built-in.a;  printf "fs/quota/%s " dquot.o quota.o kqid.o netlink.o | xargs ar cDPrST fs/quota/built-in.a
