#pragma once

#include <stdint.h>
#include <unistd.h>
#include <string.h>

namespace ws281x
{
	// TNeoPixel is the main class that does all the "magic"
	// it converts all RGB color information into a bit pattern which when sent over the SPI bus will be understood by the LEDs
	// use one of its specializations below "TWS2812B" or "TWS2811"

	// in order to use it connect SPI-MOSI pin to the input pin of your first LED
	// SPI-SCLK and SPI-MISO are not used and should not be connected

	// this method is very reliable and uses next to no CPU power on the host computer as most of the stuff is done fully in hardware
	// also this library has practically no dependencies, all it needs is an SPI bus chip spported by your kernel (like the one in the Raspberry Pi)
	// you can even run this library without root permissions, by changing the ownership settings on /dev/spidev* appropriately

	// if you use a level-shifter with an "enable" pin (like the "74AHCT1G125GW") you can continue to use the SPI bus
	// for other purposes aswell and address the LED strip as full-fledged SPI device
	// have a look here "https://easyeda.com/Neegu0Sh/neopixel-level-shifter" for how to wire everything up

	// if you do NOT use a level-shifter and your host uses 3.3V to drive the SPI bus (like the Raspberry Pi)
	// then make sure the cabeling between your host and the first LED is as short as possible
	// if you still cannot make it work, try lowering the voltage of the LEDs to 3.3V - this will reduce brightness, but usually fixes the signaling issues

	static unsigned long HZ_SPI_NEOPIXEL = 2500000;	// this yields 400ns bit-times on the bus

	template<unsigned idx_red, unsigned idx_green, unsigned idx_blue>
	struct TNeoPixel
	{
		struct TColor
		{
			uint8_t b[3];
			TColor& operator=(uint8_t);
			TColor& operator+=(uint8_t);
			TColor& operator-=(uint8_t);

			TColor(uint8_t = 0);
			operator uint8_t() const;
		} __attribute__((packed));

		TColor color[3];
		uint8_t latch_delay[2];

		TColor& Red();
		TColor& Green();
		TColor& Blue();

		const TColor& Red() const;
		const TColor& Green() const;
		const TColor& Blue() const;

		void RGB(uint8_t, uint8_t, uint8_t);

		TNeoPixel(uint8_t = 0, uint8_t = 0, uint8_t = 0);
	} __attribute__((packed));

	// use the one that matches your LED type:
	typedef TNeoPixel<1,0,2> TWS2812B;
	typedef TNeoPixel<0,1,2> TWS2811;

	struct TBar
	{
		TWS2812B* arr_pixels;
		unsigned n_pixels;

		void Set(uint8_t red, uint8_t green, uint8_t blue)
		{
			for(unsigned i = 0; i < n_pixels; i++)
				arr_pixels[i].RGB(red,green,blue);
		}

		TBar(TWS2812B* arr_pixels, unsigned offset, unsigned n_pixels) : arr_pixels(arr_pixels+offset), n_pixels(n_pixels) {}
	};

	// this is a pretty simple wrapper driver for the SPI bus
	// all it does is handle the open/close and data transfer calls to the kernel
	class TSPIDriver
	{
		private:
			TSPIDriver(const TSPIDriver&);

		protected:
			long long hz_speed;
			int fd;

		public:
			void SendData(const void* buffer, const size_t n_bytes);

			TSPIDriver(const char* const spidev, const long long hz_speed);
			~TSPIDriver();
	};

	// #####################################################################################
	// #####################################################################################
	// #####################################################################################


	template<unsigned idx_red, unsigned idx_green, unsigned idx_blue>
	TNeoPixel<idx_red, idx_green, idx_blue>::TNeoPixel(uint8_t red, uint8_t green, uint8_t blue)
	{
		this->Red() = red;
		this->Green() = green;
		this->Blue() = blue;
		memset(this->latch_delay, 0x00, sizeof(this->latch_delay));
	}

	template<unsigned idx_red, unsigned idx_green, unsigned idx_blue>
	typename TNeoPixel<idx_red, idx_green, idx_blue>::TColor& TNeoPixel<idx_red, idx_green, idx_blue>::TColor::operator=(uint8_t v)
	{
		this->b[0] = (uint8_t)(0b10010010 | ((v & 0b10000000) >> 1) | ((v & 0b01000000) >> 3) | ((v & 0b00100000) >> 5));
		this->b[1] = (uint8_t)(0b01001001 | ((v & 0b00010000) << 1) | ((v & 0b00001000) >> 1));
		this->b[2] = (uint8_t)(0b00100100 | ((v & 0b00000100) << 5) | ((v & 0b00000010) << 3) | ((v & 0b00000001) << 1));
		return *this;
	}

	template<unsigned idx_red, unsigned idx_green, unsigned idx_blue>
	TNeoPixel<idx_red, idx_green, idx_blue>::TColor::operator uint8_t() const
	{
		uint8_t r = 0;
		r |= ((this->b[0] & 0b01000000) << 1) | ((this->b[0] & 0b00001000) << 3) | ((this->b[0] & 0b00000001) << 5);
		r |= ((this->b[1] & 0b00100000) >> 1) | ((this->b[1] & 0b00000100) << 1);
		r |= ((this->b[2] & 0b10000000) >> 5) | ((this->b[2] & 0b00010000) >> 3) | ((this->b[2] & 0b00000010) >> 1);
		return r;
	}

	template<unsigned idx_red, unsigned idx_green, unsigned idx_blue>
	typename TNeoPixel<idx_red, idx_green, idx_blue>::TColor& TNeoPixel<idx_red, idx_green, idx_blue>::TColor::operator+=(uint8_t v)
	{
		*this = ((uint8_t)*this) + v;
		return *this;
	}

	template<unsigned idx_red, unsigned idx_green, unsigned idx_blue>
	typename TNeoPixel<idx_red, idx_green, idx_blue>::TColor& TNeoPixel<idx_red, idx_green, idx_blue>::TColor::operator-=(uint8_t v)
	{
		*this = ((uint8_t)*this) - v;
		return *this;
	}

	template<unsigned idx_red, unsigned idx_green, unsigned idx_blue>
	void TNeoPixel<idx_red, idx_green, idx_blue>::RGB(uint8_t r, uint8_t g, uint8_t b)
	{
		this->Red() = r;
		this->Green() = g;
		this->Blue() = b;
	}

	template<unsigned idx_red, unsigned idx_green, unsigned idx_blue>
	TNeoPixel<idx_red, idx_green, idx_blue>::TColor::TColor(uint8_t v)
	{
		*this = v;
	}

	template<unsigned idx_red, unsigned idx_green, unsigned idx_blue>
	typename TNeoPixel<idx_red, idx_green, idx_blue>::TColor& TNeoPixel<idx_red, idx_green, idx_blue>::Red()
	{
		return this->color[idx_red];
	}

	template<unsigned idx_red, unsigned idx_green, unsigned idx_blue>
	typename TNeoPixel<idx_red, idx_green, idx_blue>::TColor& TNeoPixel<idx_red, idx_green, idx_blue>::Green()
	{
		return this->color[idx_green];
	}

	template<unsigned idx_red, unsigned idx_green, unsigned idx_blue>
	typename TNeoPixel<idx_red, idx_green, idx_blue>::TColor& TNeoPixel<idx_red, idx_green, idx_blue>::Blue()
	{
		return this->color[idx_blue];
	}

	template<unsigned idx_red, unsigned idx_green, unsigned idx_blue>
	const typename TNeoPixel<idx_red, idx_green, idx_blue>::TColor& TNeoPixel<idx_red, idx_green, idx_blue>::Red() const
	{
		return this->color[idx_red];
	}

	template<unsigned idx_red, unsigned idx_green, unsigned idx_blue>
	const typename TNeoPixel<idx_red, idx_green, idx_blue>::TColor& TNeoPixel<idx_red, idx_green, idx_blue>::Green() const
	{
		return this->color[idx_green];
	}

	template<unsigned idx_red, unsigned idx_green, unsigned idx_blue>
	const typename TNeoPixel<idx_red, idx_green, idx_blue>::TColor& TNeoPixel<idx_red, idx_green, idx_blue>::Blue() const
	{
		return this->color[idx_blue];
	}
}
