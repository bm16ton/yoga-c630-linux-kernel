cmd_drivers/i2c/busses/built-in.a := rm -f drivers/i2c/busses/built-in.a;  printf "drivers/i2c/busses/%s " i2c-qcom-geni.o | xargs ar cDPrST drivers/i2c/busses/built-in.a
