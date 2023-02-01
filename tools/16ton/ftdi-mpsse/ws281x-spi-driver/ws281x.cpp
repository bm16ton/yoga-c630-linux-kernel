#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

#include "ws281x.hpp"

#define SYSERR(expr) do { if((long)(expr) == -1L) { perror(#expr); throw #expr; } } while(false)

namespace ws281x
{
	void TSPIDriver::SendData(const void* buffer, const size_t n_bytes)
	{
		struct spi_ioc_transfer xfer_cmd;
		memset(&xfer_cmd, 0, sizeof(xfer_cmd));

		xfer_cmd.tx_buf = (size_t)buffer;
		xfer_cmd.len = n_bytes;
		xfer_cmd.delay_usecs = 0;
		xfer_cmd.speed_hz = this->hz_speed;
		xfer_cmd.bits_per_word = 8;

		SYSERR(ioctl(this->fd, SPI_IOC_MESSAGE(1), &xfer_cmd));
	}

	TSPIDriver::TSPIDriver(const char* const spidev, const long long hz_speed) : hz_speed(hz_speed), fd(-1)
	{
		SYSERR(this->fd = open(spidev, O_RDWR | O_CLOEXEC | O_NOCTTY));
	}

	TSPIDriver::~TSPIDriver()
	{
		if(close(this->fd) == -1)
			perror("TSPIDriver::~TSPIDriver: failed to close handle to spidev");
	}
}

