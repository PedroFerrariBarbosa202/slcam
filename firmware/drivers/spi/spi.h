/*
 * spi.h
 *
 * Copyright The SLCam Contributors.
 *
 * This file is part of SLCam.
 *
 * SLCam is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * SLCam is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with SLCam. If not, see <http://www.gnu.org/licenses/>.
 *
 */

/**
 * \brief SPI driver definition.
 *
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * \author Carlos Augusto Porto Freitas <carlos.portof@hotmail.com>
 *
 * \version 0.2.10
 *
 * \date 2024/02/13
 *
 * \defgroup spi SPI
 * \ingroup drivers
 * \{
 */

#ifndef SPI_H_
#define SPI_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <utils/mutex/mutex.h>

#define SPI_MODULE_NAME "SPI"

/**
 * \brief SPI ports.
 */
enum spi_port {
	SPI_PORT_0, /**< SPI port 0. */
	SPI_PORT_1, /**< SPI port 1. */
	SPI_PORT_2, /**< SPI port 2. */
	SPI_PORT_3, /**< SPI port 3. */
	SPI_PORT_4, /**< SPI port 4. */
	SPI_PORT_5 /**< SPI port 5. */
};

/**
 * \brief SPI modes.
 */
enum spi_mode {
	SPI_MODE_0, /**< SPI mode 0 (Clock Polarity = 0, Clock Phase = 0). */
	SPI_MODE_1, /**< SPI mode 1 (Clock Polarity = 0, Clock Phase = 1). */
	SPI_MODE_2, /**< SPI mode 2 (Clock Polarity = 1, Clock Phase = 0). */
	SPI_MODE_3 /**< SPI mode 3 (Clock Polarity = 1, Clock Phase = 1). */
};

/**
 * \brief SPI bus configuration parameters.
 */
struct spi_config {
	uint32_t speed_hz; /**< Transfer rate in Hertz. */
	uint8_t mode; /**< SPI mode (0, 1, 2 or 3). */
};

/**
 * \brief SPI device struct. (Forward declared here)
 */
struct spi_device;

/**
 * \brief SPI bus controller struct. (Forward declared here)
 */
struct spi_controller;

struct spi_driver_api {
	int (*init)(struct spi_controller *controller, const struct spi_config *config,
		    const enum spi_port port);
	int (*configure)(struct spi_controller *controller, struct spi_config *config);
	int (*write)(struct spi_device *dev, uint8_t *buf, size_t len);
	int (*read)(struct spi_device *dev, uint8_t *buf, size_t len);
	int (*transfer)(struct spi_device *dev, uint8_t *tx_buf, size_t tx_len, uint8_t *rx_buf,
			size_t rx_len);
	int (*select_slave)(struct spi_device *dev, bool slave_state);
	int (*write_only)(struct spi_device *dev, uint8_t *buf, size_t len);
	int (*read_only)(struct spi_device *dev, uint8_t *buf, size_t len);
};

struct spi_controller {
	struct spi_driver_api api;
	struct spi_config config;
	struct mutex lock;
	uint8_t port;
	uint8_t initialized;
};

struct spi_device {
	struct spi_controller *controller;
	uint8_t cs; /* Chip select gpio pin */
	uint8_t cs_active_level; /* 1 = CS ACTIVE HIGH; 0 = CS ACTIVE LOW */
};

/**
 * \brief Initializes a SPI controller, configures it and populate its struct.
 *
 * \param[out] controller is a pointer to the SPI controller handle inside a 
 * spi_device. This needs to be a double pointer since, after initialization, 
 * this handle will be pointing to the hardware specific controller instance, 
 * avoiding, therefore, multiple instances of the same physical controller.
 * If the function returned an error this should be in an invalid state. 
 *
 * \param[in] port is the specific hardware port number of the controller.
 *
 * \param[in] config is the configuration to apply to the controller.
 *
 * \return The status/error code.
 */
int spi_init_controller(struct spi_controller **controller, const enum spi_port port,
			const struct spi_config *config);

/**
 * \brief Configures a SPI controller. It assumes that the controller is 
 * already initialized.
 *
 * \param[out] controller is the SPI controller struct to configured.
 *
 * \param[in] config is the configuration to apply to the controller.
 *
 * \return The status/error code.
 */
int spi_configure_controller(struct spi_controller *controller, struct spi_config *config);

/**
 * \brief Initializes a SPI device.
 *
 * \param[out] dev is the SPI device struct to initialized.
 *
 * \param[in] port is the SPI port controller that the device is
 * connected to. It tries to initialize
 *
 * \param[in] config is the configuration to apply to the controller. 
 * If the controller is already initialized the config is not applied, 
 * for that spi_configure_controller() should be used.
 *
 * \param[in] cs_pin is the SPI chip select gpio pin to be initialized.
 *
 * \param[in] cs_active_level is the SPI chip select active level.
 *
 * \return The status/error code.
 */
int spi_init_device(struct spi_device *dev, enum spi_port port, const struct spi_config *config,
		    const uint8_t cs_pin, const uint8_t cs_active_level);

/**
 * \brief Change the state for the CS pin of a SPI device.
 *
 * \param[in] dev is the SPI device struct.
 *
 * \param[in] state is the state to set the pin to.
 *
 * \return The status/error code.
 */
int spi_select_slave(struct spi_device *dev, bool state);

/**
 * \brief Write to a SPI device.
 *
 * \param[in] dev is the SPI device struct to write to.
 *
 * \param[in] buf is the data to be written.
 *
 * \param[in] len is the length of the buffer in bytes.
 *
 * \return The status/error code.
 */
int spi_device_write(struct spi_device *dev, uint8_t *buf, size_t len);

/**
 * \brief Write to a SPI device, without changing the chip select state.
 *
 * \param[in] dev is the SPI device struct to write to.
 *
 * \param[in] buf is the data to be written.
 *
 * \param[in] len is the length of the buffer in bytes.
 *
 * \return The status/error code.
 */
int spi_device_write_only(struct spi_device *dev, uint8_t *buf, size_t len);

/**
 * \brief Read from a SPI device.
 *
 * \param[in] dev is the SPI device struct to read from.
 *
 * \param[out] buf is a buffer where read data is stored.
 *
 * \param[in] len is the number of bytes to be read.
 *
 * \return The number of bytes read, if errors occured the function returns 
 * negative numbers.
 */
int spi_device_read(struct spi_device *dev, uint8_t *buf, size_t len);

/**
 * \brief Read from a SPI device, without changing the chip select state.
 *
 * \param[in] dev is the SPI device struct to read from.
 *
 * \param[out] buf is a buffer where read data is stored.
 *
 * \param[in] len is the number of bytes to be read.
 *
 * \return The number of bytes read, if errors occured the function returns 
 * negative numbers.
 */
int spi_device_read_only(struct spi_device *dev, uint8_t *buf, size_t len);

/**
 * \brief Perform a transfer with a SPI device.
 *
 * \param[in] dev is the SPI device struct.
 *
 * \param[in] tx_buf is the data to be written.
 *
 * \param[in] tx_len is the length of the buffer in bytes.
 *
 * \param[out] rx_buf is a buffer where read data is stored.
 *
 * \param[in] rx_len is the number of bytes to be read.
 *
 * \return The number of bytes read, if errors occured the function returns 
 * negative numbers.
 */
int spi_device_transfer(struct spi_device *dev, uint8_t *tx_buf, size_t tx_len, uint8_t *rx_buf,
			size_t rx_len);

/**
 * \brief Get hardware specific spi driver functions struct. THIS FUNCTION 
 * SHOULD BE IMPLEMENTED FOR EACH CPU, otherwise the driver does not work.
 *
 * \return The struct containing the hardware specific functions. 
 */
extern struct spi_driver_api *spi_hw_get_driver(void);

/**
 * \brief Get hardware specific controller instances, this is done to provide 
 * a `singleton` like controllers to avoid concurrency issues. THIS FUNCTION
 * SHOULD BE IMPLEMENTED FOR EACH CPU, otherwise the driver does not work. It 
 * could be implemented simply by: 
 *
 * static struct spi_controller *controller_list[] = {
 *      [SPI_PORT_0] = &spi_controller_0,
 *      [SPI_PORT_1] = &spi_controller_1,
 *      ...
 *      [SPI_PORT_5] = &spi_controller_5,
 * }
 *
 * struct spi_controller *spi_hw_get_controller_handle(enum spi_port port) {
 *      return controller_list[port];
 * }
 *
 * \param[in] port is the hardware port to identify the controller.
 *
 * \return The struct containing the matching controller handle.
 */
extern struct spi_controller *spi_hw_get_controller_handle(enum spi_port port);

#endif /* SPI_H_ */

/** \} End of spi group */
