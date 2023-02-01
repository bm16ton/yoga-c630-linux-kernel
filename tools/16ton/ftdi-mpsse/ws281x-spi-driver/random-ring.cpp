#include "util.hpp"

using namespace ws281x;

int main()
{
	// compute delay
	const float fps = 10;
	const unsigned delay = lrint(1000000.0f / fps);

	// our LED ring will have 60 LEDs...
	const unsigned n_pixels = 16;

	// ... but the buffer for the ring will need to be twice the size (in order for the pointer-shifting in RunRing() to work)
	TWS2812B arr_pixels[n_pixels * 2];

	// initialize the random number generator based on the current time
	srand(time(NULL));

	// randomize the RGB data
	for(unsigned i = 0; i < n_pixels; i++)
	{
		arr_pixels[i].RGB(
			(rand() % 256) / 16,
			(rand() % 256) / 16,
			(rand() % 256) / 16
		);

	}

	// duplicate first half of the ring-buffer into the second half (required for RunRing() to work)
	memcpy(arr_pixels + n_pixels, arr_pixels, n_pixels * sizeof(TWS2812B));

	// run the show!
	RunRing(arr_pixels, n_pixels, delay);

	// c++ destructors will take care of proper shutdown and release of resources...
	return 0;
}
