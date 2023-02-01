.PHONY: all clean run check

all: simple firefly-ring random-ring off temp color fire-flicker fade

off: ws281x.cpp off.cpp
	g++ -O3 -flto -fwhole-program -Wall -Wextra -Wno-unused-function -Wno-unused-variable -g ws281x.cpp off.cpp -o off

simple: ws281x.cpp simple.cpp
	g++ -O3 -flto -fwhole-program -Wall -Wextra -Wno-unused-function -Wno-unused-variable -g ws281x.cpp simple.cpp -o simple

temp: ws281x.cpp temp.cpp util.hpp
	g++ -O3 -flto -fwhole-program -Wall -Wextra -Wno-unused-function -Wno-unused-variable -g ws281x.cpp temp.cpp -o temp

color: ws281x.cpp color.cpp
	g++ -O3 -flto -fwhole-program -Wall -Wextra -Wno-unused-function -Wno-unused-variable -g ws281x.cpp color.cpp -o color

firefly-ring: ws281x.cpp firefly-ring.cpp util.hpp
	g++ -O3 -flto -fwhole-program -Wall -Wextra -Wno-unused-function -Wno-unused-variable -g ws281x.cpp firefly-ring.cpp -o firefly-ring

random-ring: ws281x.cpp random-ring.cpp util.hpp
	g++ -O3 -flto -fwhole-program -Wall -Wextra -Wno-unused-function -Wno-unused-variable -g ws281x.cpp random-ring.cpp -o random-ring

fire-flicker: ws281x.cpp fire-flicker.cpp
	g++ -O3 -flto -fwhole-program -Wall -Wextra -Wno-unused-function -Wno-unused-variable -g ws281x.cpp fire-flicker.cpp -o fire-flicker

fade: ws281x.cpp fade.cpp
	g++ -O3 -flto -fwhole-program -Wall -Wextra -Wno-unused-function -Wno-unused-variable -g ws281x.cpp fade.cpp -o fade

clean:
	rm -vf simple firefly-ring random-ring off temp color fire-flicker
