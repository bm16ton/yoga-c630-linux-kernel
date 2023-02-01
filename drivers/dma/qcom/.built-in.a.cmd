cmd_drivers/dma/qcom/built-in.a := rm -f drivers/dma/qcom/built-in.a;  printf "drivers/dma/qcom/%s " bam_dma.o | xargs ar cDPrST drivers/dma/qcom/built-in.a
