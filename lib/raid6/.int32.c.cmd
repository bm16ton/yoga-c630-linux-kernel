cmd_lib/raid6/int32.c := awk -v N=32 -f ./lib/raid6/unroll.awk < lib/raid6/int.uc > lib/raid6/int32.c
