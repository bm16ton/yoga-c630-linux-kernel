cmd_lib/raid6/neon4.c := awk -v N=4 -f ./lib/raid6/unroll.awk < lib/raid6/neon.uc > lib/raid6/neon4.c
