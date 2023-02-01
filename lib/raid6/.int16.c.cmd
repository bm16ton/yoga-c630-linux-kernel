cmd_lib/raid6/int16.c := awk -v N=16 -f ./lib/raid6/unroll.awk < lib/raid6/int.uc > lib/raid6/int16.c
