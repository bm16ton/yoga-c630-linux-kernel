cmd_drivers/thermal/qcom/built-in.a := rm -f drivers/thermal/qcom/built-in.a;  printf "drivers/thermal/qcom/%s " lmh.o | xargs ar cDPrST drivers/thermal/qcom/built-in.a
