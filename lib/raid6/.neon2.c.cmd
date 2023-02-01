cmd_lib/raid6/neon2.c := awk -v N=2 -f ./lib/raid6/unroll.awk < lib/raid6/neon.uc > lib/raid6/neon2.c
