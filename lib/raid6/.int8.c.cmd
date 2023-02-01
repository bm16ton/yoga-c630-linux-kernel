cmd_lib/raid6/int8.c := awk -v N=8 -f ./lib/raid6/unroll.awk < lib/raid6/int.uc > lib/raid6/int8.c
