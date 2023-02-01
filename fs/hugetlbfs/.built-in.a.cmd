cmd_fs/hugetlbfs/built-in.a := rm -f fs/hugetlbfs/built-in.a;  printf "fs/hugetlbfs/%s " inode.o | xargs ar cDPrST fs/hugetlbfs/built-in.a
