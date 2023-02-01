#include "ws281x.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sched.h>

using namespace ws281x;

static double GetTime()
{
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return (double)ts.tv_sec + (double)ts.tv_nsec / 1000000000.0;
}

static double DelayAndGetTime(const double ts_prev, const double ts_min = 0.01)
{
	double ts_now = GetTime();
	const double d = ts_now - ts_prev;
	if(d < ts_min)
		usleep( (ts_min - d) * 1000000 );
	return GetTime();
}

static void SetRealtimeScheduling()
{
	// requires root powers (but non-fatal)
	struct sched_param s;
	memset(&s, 0, sizeof(s));
	s.sched_priority = 1;
	sched_setscheduler(0, SCHED_FIFO, &s);
}

int main(int argc, char* argv[])
{
	// fade from one color to another

	SetRealtimeScheduling();

	unsigned char red_from,green_from,blue_from;
	unsigned char red_to,green_to,blue_to;

	if(
		argc != 4 ||
		sscanf(argv[1], "%hhx:%hhx:%hhx", &red_from, &green_from, &blue_from) != 3 ||
		sscanf(argv[2], "%hhx:%hhx:%hhx", &red_to,   &green_to,   &blue_to)   != 3
	)
	{
		fprintf(stderr, "ERROR: usage is: '%s' <RR>:<GG>:<BB> <RR>:<GG>:<BB> <fade time>\n\twhere RR, GG and BB are hexadecimal numbers (00 to ff) representing the RGB color\n\tfade time is a floting-point number in seconds\n", argv[0]);
		return 1;
	}

	const double red_diff   = red_to   - red_from;
	const double green_diff = green_to - green_from;
	const double blue_diff  = blue_to  - blue_from;

// 	fprintf(stderr, "diff = { %g, %g, %g }\n", red_diff, green_diff, blue_diff);

	// attach an instance of the SPI-driver to the first SPI device on the first bus (0.0)
	TSPIDriver spi_dev_1("/dev/spidev16.0", HZ_SPI_NEOPIXEL);

	const unsigned n_pixels = 60;
	TWS2812B arr_pixels[n_pixels];

	const double time_fade = atof(argv[3]);
	const double ts_start = GetTime();
	const double ts_end = ts_start + time_fade;

	double ts_prev = ts_start;

	for(;;)
	{
		const double ts_now = DelayAndGetTime(ts_prev, 0.01);
		const double time_elapsed = ts_now - ts_start;
		const float progress = fmax(0.0, fmin(1.0, time_elapsed / time_fade));
		const unsigned char red   = rint(red_from   + red_diff   * progress);
		const unsigned char green = rint(green_from + green_diff * progress);
		const unsigned char blue  = rint(blue_from  + blue_diff  * progress);

// 		fprintf(stderr, "ts_start = %f, ts_end = %f, ts_now = %f, progress = %g\n", ts_start, ts_end, ts_now, progress);

		for(unsigned i = 0; i < n_pixels; i++)
			arr_pixels[i].RGB(red, green, blue);

		// now we send the data to the LEDs:
		spi_dev_1.SendData(arr_pixels, sizeof(arr_pixels));

		if(ts_now >= ts_end)
			break;

		ts_prev = ts_now;
	}

	// c++ destructors will take care of proper shutdown and release of resources...
	return 0;
}
