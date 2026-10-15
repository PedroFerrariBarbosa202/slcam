#include <stdint.h>
#include <config/errno.h>
#include <drivers/spi/spi.h>

#define SPI_TEST_CS_PIN (0x04U)

static void delay(volatile uint32_t n)
{
	while (n--)
		;
}

int main(void)
{
	int err;

	struct spi_config config = {
		.speed_hz = 1000000,
		.mode = SPI_MODE_0,
	};

	struct spi_device dev = { 0 };

	err = spi_init_device(&dev, SPI_PORT_0, &config, SPI_TEST_CS_PIN, 1U);
	if (err < 0) {
		while (1)
			;
	}

	uint8_t tx[8] = { 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40 };
	uint8_t rx[8] = { 0 };

	while (1) {
		err = spi_device_transfer(&dev, tx, sizeof(tx), rx, sizeof(rx));
		(void)err;

		delay(100000);
	}
}
