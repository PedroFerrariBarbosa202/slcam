/*
 * gpio.h
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
 * \brief GPIO driver definition.
 *
 * \author Carlos Augusto Porto Freitas <carlos.portof@hotmail.com>
 *
 * \version 0.2.10
 *
 * \date 2025/01/12
 *
 * \defgroup gpio gpio
 * \ingroup drivers
 * \{
 */

#ifndef GPIO_H_
#define GPIO_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <utils/macros/macros.h>

#define GPIO_MODULE_NAME "GPIO"

#define GPIO_STATE_LOW 0
#define GPIO_STATE_HIGH 1

#define GPIO_PIN_TO_BIT(pin) (__BIT(pin))

/**
 * \brief GPIO mode enum.
 */
enum gpio_mode {
	GPIO_DRV_MODE_OUTPUT_PUSH_PULL,
	GPIO_DRV_MODE_OUTPUT_OPEN_DRAIN,
	GPIO_DRV_MODE_INPUT_FLOATING,
	GPIO_DRV_MODE_INPUT_PULL_UP,
	GPIO_DRV_MODE_INPUT_PULL_DOWN,
};

/**
 * \brief GPIO ports enum.
 */
enum gpio_port {
	GPIO_PORT_0,
	GPIO_PORT_1,
	GPIO_PORT_2,
	GPIO_PORT_3,
	GPIO_PORT_4,
	GPIO_PORT_5,
	GPIO_PORT_6,
	GPIO_PORT_7,
	GPIO_PORT_8,
};

/* Macros to define letter based ports */
#define GPIO_PORT_A GPIO_PORT_0
#define GPIO_PORT_B GPIO_PORT_1
#define GPIO_PORT_C GPIO_PORT_2
#define GPIO_PORT_D GPIO_PORT_3
#define GPIO_PORT_E GPIO_PORT_4
#define GPIO_PORT_F GPIO_PORT_5

struct gpio_driver_api {
	int (*init)(const uint8_t pin, const uint8_t mode);
	int (*set_mode)(const uint8_t pin, const uint8_t mode);
	int (*set_state)(const uint8_t pin, bool state);
	int (*get_state)(const uint8_t pin);
	int (*toggle)(const uint8_t pin);
	int (*set_state_mask)(const uint8_t gpio_port, const uint32_t pin_mask,
			      const uint32_t state_mask);
	int32_t (*get_state_mask)(const uint8_t gpio_port,
				  const uint32_t pin_mask);
	int64_t (*convert_port_to_pin_num)(const uint8_t gpio_port,
					   const uint8_t port_pin);
};

/**
 * \brief Initializes GPIO driver, checking if the hardware specific API is 
 * defined correctly.
 *
 * \return The status/error code.
 */
int gpio_init_driver(void);

/**
 * \brief Initializes a GPIO pin.
 *
 * \param[in] pin is the specific hardware gpio pin number. 
 *
 * \param[in] mode is the gpio mode to initialize.
 *
 * \return The status/error code.
 */
int gpio_init_pin(const uint8_t pin, const enum gpio_mode mode);

/**
 * \brief Sets a GPIO pin mode.
 *
 * \param[in] pin is the specific hardware gpio pin number. 
 *
 * \param[in] mode is the gpio mode to initialize.
 *
 * \return The status/error code.
 */
int gpio_set_pin_mode(const uint8_t pin, const enum gpio_mode mode);

/**
 * \brief Sets the state of GPIO pin.
 *
 * \param[in] pin is the specific hardware gpio pin number. 
 *
 * \param[in] mode is the gpio mode to initialize.
 *
 * \return The status/error code.
 */
int gpio_set_state(const uint8_t pin, const bool state);

/**
 * \brief Gets the state of GPIO pin.
 *
 * \param[in] pin is the specific hardware gpio pin number. 
 *
 * \return The gpio pin state. Can return a negative value in case of an error.
 */
int gpio_get_state(const uint8_t pin);

/**
 * \brief Toggles the state of GPIO pin.
 *
 * \param[in] pin is the specific hardware gpio pin number. 
 *
 * \return The status/error code.
 */
int gpio_state_toggle(const uint8_t pin);

/**
 * \brief Gets the state of GPIO pin.
 *
 * \param[in] gpio_port is the specific hardware gpio pin port. 
 *
 * \param[in] pin_mask is a bit mask with the desired pins to read.
 *
 * \return The state of the pins.
 * (Ex: gpio_get_state_mask(GPIO_PIN_TO_BIT(12) | GPIO_PIN_TO_BIT(1)) -> 0b0000000000000000000X0000000000X0 
 * where X is the current state of pin. If an error occurred then a negative errno code is returned.
 */
int32_t gpio_get_state_mask(const uint8_t gpio_port, const uint32_t pin_mask);

/**
 * \brief Sets the state of GPIO pin.
 *
 * \param[in] gpio_port is the specific hardware gpio pin port. 
 *
 * \param[in] pin_mask is a bit mask with the desired pins to set its state.
 *
 * \param[in] state_mask is a bit mask with the desired state for the pins; 
 *
 * \return The status/error code.
 */
int gpio_set_state_mask(const uint8_t gpio_port, const uint32_t pin_mask,
			const uint32_t state_mask);

/**
 * \brief Sets the state of GPIO pin.
 *
 * \param[in] gpio_port is the specific hardware gpio pin port. 
 *
 * \param[in] port_pin is the gpio mode to initialize.
 *
 * \return The specified gpio port/pin pair converted to raw pin number. 
 * Could return a negative value in case the combination is not defined.
 */
int64_t gpio_convert_port_to_pin_num(const uint8_t gpio_port,
				     const uint8_t port_pin);

/**
 * \brief Get hardware specific gpio driver functions struct. THIS FUNCTION 
 * SHOULD BE IMPLEMENTED FOR EACH CPU, otherwise the driver does not work.
 *
 * \return The struct containing the hardware specific functions. 
 */
extern struct gpio_driver_api *gpio_hw_get_driver(void);

#endif /* GPIO_H_ */

/** \} End of gpio group */
