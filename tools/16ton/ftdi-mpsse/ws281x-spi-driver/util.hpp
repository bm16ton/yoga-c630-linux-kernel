#pragma once

#include "ws281x.hpp"
#include <stdlib.h>
#include <time.h>
#include <math.h>

namespace ws281x
{
	static void RunRing(const TWS2812B* const arr, const unsigned n_pixels, const unsigned delay)
	{
		// attach an instance of the SPI-driver to the first SPI device on the first bus (0.0)
		// set the transfer speed to 2500000 Hz (required to drive NeoPixels)
		TSPIDriver spi_dev_1("/dev/spidev16.4", HZ_SPI_NEOPIXEL);

		unsigned i = 0;
		for(;;)
		{
			spi_dev_1.SendData(arr + i, sizeof(TWS2812B) * n_pixels);
			usleep(delay);

			i++;
			if(i >= n_pixels)
				i = 0;
		}
	}

	static void GenerateBarGraph(TWS2812B* arr_pixels, const unsigned n_pixels, const bool reverse, const float value, const char red, const char green, const char blue)
	{
		const unsigned n_on = lrint((float)n_pixels * value);

		for(unsigned i = 0; i < n_pixels; i++)
		{
			TWS2812B& pixel = arr_pixels[(reverse ? (n_pixels - i - 1) : i)];

			if(i < n_on)
				pixel.RGB(red,green,blue);
			else
				pixel.RGB(0,0,0);
		}
	}

	static float Limit01(const float v)
	{
		if(v < 0) return 0;
		if(v > 1) return 1;
		return v;
	}
}
