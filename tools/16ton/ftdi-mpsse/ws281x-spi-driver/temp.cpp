#include "util.hpp"
#include <stdio.h>
using namespace ws281x;

int main()
{
	// read input stream in CSV format and display temperature and humidity as bar graphs
	// format: <time1-sec>.<time1-nano>;<time2-sec>.<time2-nano>;<temp-float>;<humidity-float>
	// the timestamps are not used for anything

	// attach an instance of the SPI-driver to the first SPI device on the first bus (0.0)
	TSPIDriver spi_dev_1("/dev/spidev16.4", HZ_SPI_NEOPIXEL);

	// our LED strip or ring will have 60 LEDs
	const unsigned n_pixels = 60;
	TWS2812B arr_pixels[n_pixels];

	float temp, hum;
	while(scanf("%*u.%*u;%*u.%*u;%f;%f", &temp, &hum) == 2)
	{
// 		fprintf(stderr, "DEBUG: temp-v = %f; hum-v = %f\n", temp, hum);

		temp -= 15.0f;
		temp /= 20.0f;
		hum /= 100.0f;

// 		fprintf(stderr, "DEBUG: temp-f = %f; hum-f = %f\n", temp, hum);

		GenerateBarGraph(arr_pixels,              n_pixels/2, false, Limit01(temp), 1, 0, 0);
		GenerateBarGraph(arr_pixels + n_pixels/2, n_pixels/2, true,  Limit01(hum),  0, 0, 1);

		// send the data to the LEDs:
		spi_dev_1.SendData(arr_pixels, sizeof(arr_pixels));

// 		putc('\n', stderr);
	}

	// c++ destructors will take care of proper shutdown and release of resources...
	return 0;
}
