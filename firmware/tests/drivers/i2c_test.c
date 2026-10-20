#include <stdint.h>
#include <config/errno.h>
#include <drivers/i2c/i2c.h>

#define SPI_TEST_CS_PIN (0x04U)

static void delay(volatile uint32_t n)
{
	while (n--)
		;
}

int main(void)
{
	int err;

	struct i2c_config config = {
		.speed_hz = i2c_speed_fm_400k,
		.clock_freq_mhz = 36,
	};

	struct i2c_device dev = { 0 };

	err = i2c_init_device(&dev, I2C_PORT_0, &config);

	uint8_t tx[8] = { 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40 };

	while (1) {
		err = i2c_device_write(&dev, 0x50, tx, sizeof(tx));
		(void)err;

		delay(100000);
	}
}
