#include "ws281x.hpp"
using namespace ws281x;

int main()
{
	// switch all LEDs off

	// attach an instance of the SPI-driver to the first SPI device on the first bus (0.0)
	TSPIDriver spi_dev_1("/dev/spidev16.0", HZ_SPI_NEOPIXEL);

	// our LED strip or ring can have at most 372 LEDs
	const unsigned n_pixels = 372;
	TWS2812B arr_pixels[n_pixels];

	// and we want them to be off
	for(unsigned i = 0; i < n_pixels; i++)
		arr_pixels[i].RGB(0,0,0);

	// now we send the data to the LEDs:
	spi_dev_1.SendData(arr_pixels, sizeof(arr_pixels));

	// c++ destructors will take care of proper shutdown and release of resources...
	return 0;
}
