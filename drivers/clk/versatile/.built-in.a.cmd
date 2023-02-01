cmd_drivers/clk/versatile/built-in.a := rm -f drivers/clk/versatile/built-in.a;  printf "drivers/clk/versatile/%s " clk-vexpress-osc.o | xargs ar cDPrST drivers/clk/versatile/built-in.a
