/*
 * gpio_stm32f103.c
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
 * \brief STM32F103 GPIO driver implementation.
 *
 * \author Carlos Augusto Porto Freitas <carlos.portof@hotmail.com>
 *
 * \version 0.2.10
 *
 * \date 2024/01/12
 *
 * \addtogroup gpio
 * \{
 */

#include <stdint.h>
#include <config/errno.h>
#include <hal/include/libopencm3/stm32/gpio.h>
#include <hal/include/libopencm3/stm32/rcc.h>
#include <utils/macros/macros.h>

#include "gpio.h"

struct gpio_pin {
	uint32_t port;
	uint32_t pin;
};

static inline __always_inline uint32_t select_gpio_port(const uint8_t port)
{
	uint32_t p;

	switch (port) {
	case GPIO_PORT_0:
		p = GPIOA;
		break;
	case GPIO_PORT_1:
		p = GPIOB;
		break;
	case GPIO_PORT_2:
		p = GPIOC;
		break;
	default:
		p = UINT32_MAX;
		break;
	}

	return port;
}

static int convert_pin_num_to_port(struct gpio_pin *gpio, const uint8_t pin)
{
	uint8_t port = pin >> 4U;

	if (port >= 3)
		return -ERRNO_DRIVER_NO_PORT;

	gpio->port = select_gpio_port(port);

	gpio->pin = GPIO_PIN_TO_BIT(pin & 0x0F);

	return 0;
}

int gpio_init_stm32(const uint8_t pin, const uint8_t mode)
{
	struct gpio_pin gpio;
	int err;
	uint8_t md;
	uint8_t cnf;

	err = convert_pin_num_to_port(&gpio, pin);

	if (err < 0)
		return err;

	switch (gpio.port) {
	case GPIOA:
		rcc_periph_clock_enable(RCC_GPIOA);
		break;
	case GPIOB:
		rcc_periph_clock_enable(RCC_GPIOB);
		break;
	case GPIOC:
		rcc_periph_clock_enable(RCC_GPIOC);
		break;
	default:
		return -ERRNO_DRIVER_NO_PORT;
	}

	switch (mode) {
	case GPIO_DRV_MODE_INPUT_PULL_UP:
		md = GPIO_MODE_INPUT;
		cnf = GPIO_CNF_INPUT_PULL_UPDOWN;
		break;
	case GPIO_DRV_MODE_INPUT_PULL_DOWN:
		md = GPIO_MODE_INPUT;
		cnf = GPIO_CNF_INPUT_PULL_UPDOWN;
		break;
	case GPIO_DRV_MODE_INPUT_FLOATING:
		md = GPIO_MODE_INPUT;
		cnf = GPIO_CNF_INPUT_FLOAT;
		break;
	case GPIO_DRV_MODE_OUTPUT_PUSH_PULL:
		md = GPIO_MODE_OUTPUT_50_MHZ;
		cnf = GPIO_CNF_OUTPUT_PUSHPULL;
		break;
	case GPIO_DRV_MODE_OUTPUT_OPEN_DRAIN:
		md = GPIO_MODE_OUTPUT_50_MHZ;
		cnf = GPIO_CNF_OUTPUT_OPENDRAIN;
		break;
	default:
		return -ERRNO_DRIVER_NO_PARAMETER;
	}

	gpio_set_mode(gpio.port, md, cnf, gpio.pin);

	return 0;
}

int gpio_set_mode_stm32(const uint8_t pin, const uint8_t mode)
{
	struct gpio_pin gpio;
	int err;
	uint8_t md;
	uint8_t cnf;

	err = convert_pin_num_to_port(&gpio, pin);

	if (err < 0)
		return err;

	switch (mode) {
	case GPIO_DRV_MODE_INPUT_PULL_UP:
		md = GPIO_MODE_INPUT;
		cnf = GPIO_CNF_INPUT_PULL_UPDOWN;
		break;
	case GPIO_DRV_MODE_INPUT_PULL_DOWN:
		md = GPIO_MODE_INPUT;
		cnf = GPIO_CNF_INPUT_PULL_UPDOWN;
		break;
	case GPIO_DRV_MODE_INPUT_FLOATING:
		md = GPIO_MODE_INPUT;
		cnf = GPIO_CNF_INPUT_FLOAT;
		break;
	case GPIO_DRV_MODE_OUTPUT_PUSH_PULL:
		md = GPIO_MODE_OUTPUT_50_MHZ;
		cnf = GPIO_CNF_OUTPUT_PUSHPULL;
		break;
	case GPIO_DRV_MODE_OUTPUT_OPEN_DRAIN:
		md = GPIO_MODE_OUTPUT_50_MHZ;
		cnf = GPIO_CNF_OUTPUT_OPENDRAIN;
		break;
	default:
		return -ERRNO_DRIVER_NO_PARAMETER;
	}

	gpio_set_mode(gpio.port, md, cnf, gpio.pin);

	return 0;
}

int gpio_set_state_stm32(const uint8_t pin, const bool state)
{
	struct gpio_pin gpio;
	int err;

	err = convert_pin_num_to_port(&gpio, pin);

	if (err < 0)
		return err;

	if (state)
		gpio_set(gpio.port, gpio.pin);
	else
		gpio_clear(gpio.port, gpio.pin);

	return 0;
}

int gpio_get_state_stm32(const uint8_t pin)
{
	struct gpio_pin gpio;
	uint16_t reg;
	int err;

	err = convert_pin_num_to_port(&gpio, pin);

	if (err < 0)
		return err;

	reg = gpio_get(gpio.port, gpio.pin);

	return READ_BIT(reg, gpio.pin);
}

int gpio_toggle_stm32(const uint8_t pin)
{
	struct gpio_pin gpio;
	int err;

	err = convert_pin_num_to_port(&gpio, pin);

	if (err < 0)
		return err;

	gpio_toggle(gpio.port, gpio.pin);

	return 0;
}

int gpio_set_state_mask_stm32(const uint8_t gpio_port, const uint32_t pin_mask,
			      const uint32_t state_mask_stm32)
{
	uint32_t port;

	if ((gpio_port >= 3) || (pin_mask > 0x0F))
		return -ERRNO_DRIVER_NO_PORT;

	port = select_gpio_port(gpio_port);

	gpio_port_write(port, state_mask_stm32);

	return 0;
}

int32_t gpio_get_state_mask_stm32(const uint8_t gpio_port, const uint32_t pin_mask)
{
	uint32_t port;

	if ((gpio_port >= 3) || (pin_mask > 0x0F))
		return -ERRNO_DRIVER_NO_PORT;

	port = select_gpio_port(gpio_port);

	return gpio_get(port, pin_mask);
}

int64_t gpio_convert_port_to_pin_num_stm32(const uint8_t gpio_port, const uint8_t port_pin)
{
	int64_t pin_num = 0;

	if ((gpio_port >= 3) || (port_pin > 0x0F))
		return -ERRNO_DRIVER_NO_PORT;

	pin_num = port_pin;
	pin_num |= (gpio_port << 4U);

	return pin_num;
}

static struct gpio_driver_api stm32_driver = {
	.init = gpio_init_stm32,
	.set_mode = gpio_set_mode_stm32,
	.set_state = gpio_set_state_stm32,
	.get_state = gpio_get_state_stm32,
	.toggle = gpio_toggle_stm32,
	.set_state_mask = gpio_set_state_mask_stm32,
	.get_state_mask = gpio_get_state_mask_stm32,
	.convert_port_to_pin_num = gpio_convert_port_to_pin_num_stm32,
};

struct gpio_driver_api *gpio_hw_get_driver(void)
{
	return &stm32_driver;
}

/** \} End of gpio group */
