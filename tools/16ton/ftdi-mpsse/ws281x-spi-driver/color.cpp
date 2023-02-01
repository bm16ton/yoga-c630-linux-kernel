#include "ws281x.hpp"
#include <stdio.h>

using namespace ws281x;

int main(int argc, char* argv[])
{
	// set one color passed on the command-line to all LEDs

	unsigned char red,green,blue;

	if(argc != 2 || sscanf(argv[1], "%hhx:%hhx:%hhx", &red, &green, &blue) != 3)
	{
		fprintf(stderr, "ERROR: usage is: '%s' <RR>:<GG>:<BB>\nwhere RR, GG and BB are hexadecimal numbers\n", argv[0]);
		return 1;
	}

	// attach an instance of the SPI-driver to the first SPI device on the first bus (0.0)
	TSPIDriver spi_dev_1("/dev/spidev16.4", HZ_SPI_NEOPIXEL);

	const unsigned n_pixels = 64;
	TWS2812B arr_pixels[n_pixels];

	for(unsigned i = 0; i < n_pixels; i++)
		arr_pixels[i].RGB(red, green, blue);

	// now we send the data to the LEDs:
	spi_dev_1.SendData(arr_pixels, sizeof(arr_pixels));

	// c++ destructors will take care of proper shutdown and release of resources...
	return 0;
}
