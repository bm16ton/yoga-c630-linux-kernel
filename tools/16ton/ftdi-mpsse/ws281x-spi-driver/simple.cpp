#include "ws281x.hpp"
using namespace ws281x;

int main()
{
	// a small example

	// attach an instance of the SPI-driver to the first SPI device on the first bus (0.0)
	TSPIDriver spi_dev_1("/dev/spidev16.4", HZ_SPI_NEOPIXEL);

	// our LED strip or ring will have 60 LEDs
	const unsigned n_pixels = 16;
	TWS2812B arr_pixels[n_pixels];

	// and we want them to light up in a warm yellow
	for(unsigned i = 0; i < n_pixels; i++)
		arr_pixels[i].RGB(32,20,0);

	// now we send the data to the LEDs:
	spi_dev_1.SendData(arr_pixels, sizeof(arr_pixels));

	// c++ destructors will take care of proper shutdown and release of resources...
	return 0;
}
