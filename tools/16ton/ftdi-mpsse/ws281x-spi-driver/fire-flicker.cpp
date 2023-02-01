#include "ws281x.hpp"
#include <time.h>
#include <stdlib.h>
#include <math.h>
using namespace ws281x;

int main()
{
	// compute delay
	const float fps = 10;
	const unsigned delay = lrint(1000000.0f / fps);

	// attach an instance of the SPI-driver to the first SPI device on the first bus (0.0)
	TSPIDriver spi_dev_1("/dev/spidev16.4", HZ_SPI_NEOPIXEL);
	TWS2812B led;

	srand(time(NULL));

	for(;;)
	{
		led.RGB(
			16 + rand() % 128,
			16 + rand() % 128,
			0
		);

		spi_dev_1.SendData(&led, sizeof(led));
		usleep(delay);
	}

	// c++ destructors will take care of proper shutdown and release of resources...
	return 0;
}
