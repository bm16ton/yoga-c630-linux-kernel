#include "util.hpp"
using namespace ws281x;

static void MakeFirefly(TWS2812B* arr, const unsigned len, const unsigned char start_red, const unsigned char start_green, const unsigned char start_blue)
{
	arr[0].RGB(start_red, start_green, start_blue);

	const float dr = (float)start_red   / (float)(len-1);
	const float dg = (float)start_green / (float)(len-1);
	const float db = (float)start_blue  / (float)(len-1);

	float r = start_red;
	float g = start_green;
	float b = start_blue;

	for(unsigned i = 1; i < len; i++)
	{
		r -= dr;
		g -= dg;
		b -= db;

		arr[i].RGB(lrint(r),lrint(g),lrint(b));
	}
}

int main()
{
	// compute delay
	const float fps = 40;
	const unsigned delay = lrint(1000000.0f / fps);

	// our LED ring will have 60 LEDs...
	const unsigned n_pixels = 16;

	// ... but the buffer for the ring will need to be twice the size (in order for the pointer-shifting in RunRing() to work)
	TWS2812B arr_pixels[n_pixels * 2];

	// generate the RGB data for the three fireflies
	MakeFirefly(arr_pixels + n_pixels * 0/3, n_pixels / 6, 10, 0, 0);
	MakeFirefly(arr_pixels + n_pixels * 1/3, n_pixels / 6, 0, 10, 0);
	MakeFirefly(arr_pixels + n_pixels * 2/3, n_pixels / 6, 0, 0, 10);

	// duplicate first half of the ring-buffer into the second half (required for RunRing() to work)
	memcpy(arr_pixels + n_pixels, arr_pixels, n_pixels * sizeof(TWS2812B));

	// run the show!
	RunRing(arr_pixels, n_pixels, delay);

	// c++ destructors will take care of proper shutdown and release of resources...
	return 0;
}
