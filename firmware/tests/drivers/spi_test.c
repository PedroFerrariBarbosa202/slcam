#include <stdint.h>
#include <config/errno.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/spi.h>
#include <drivers/spi/spi.h>

static void rcc_setup(void)
{
    /*
     * Enable GPIOA and SPI1 clocks.
     *
     * SPI1 is connected to APB2.
     */
    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_SPI1);
}

int main(void)
{
    int errno = ERRNO_SUCCESS;
    rcc_setup();

    struct spi_config config = {
    .speed_hz = 1000000,  // 1 MHz
    .mode = SPI_MODE_0    // SPI mode 0
    };    

    struct spi_controller* controller = spi_hw_get_controller_handle(SPI_PORT_0);
    errno = spi_init_controller(&controller, SPI_PORT_0, &config);

    struct spi_device dev = {0};
    dev.controller = controller;

    uint8_t tx = 0x40;
    uint8_t rx = 0x00;

    errno = spi_device_transfer(&dev, &tx, 1, &rx, 1);

    while (1) {
    }

    return errno;
}
