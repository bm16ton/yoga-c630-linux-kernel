cmd_samples/built-in.a := rm -f samples/built-in.a;  printf "samples/%s " vfio-mdev/built-in.a | xargs ar cDPrST samples/built-in.a
