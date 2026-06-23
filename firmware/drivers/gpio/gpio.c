/*
 * gpio.c
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
 * along with SLCam. If not, see <http:/\/www.gnu.org/licenses/>.
 * 
 */

/**
 * \brief GPIO driver implementation.
 *
 * \author Carlos Augusto Porto Freitas <carlos.portof@hotmail.com>
 *
 * \version 0.2.10
 *
 * \date 2025/01/12
 *
 * \addtogroup gpio gpio
 * \{
 */

#include <config/errno.h>

#include "gpio.h"

int gpio_init_driver(void)
{
	const struct gpio_driver_api *drv = gpio_hw_get_driver();

	if (drv == NULL)
		return -ERRNO_DRIVER_NO_HW_IMPL;

	if (!drv->init || !drv->toggle || !drv->get_state || !drv->set_mode ||
	    !drv->set_state || !drv->get_state_mask ||
	    !drv->convert_port_to_pin_num)
		return -ERRNO_DRIVER_NO_HW_IMPL;

	return 0;
}

int gpio_init_pin(const uint8_t pin, const enum gpio_mode mode)
{
	const struct gpio_driver_api *drv = gpio_hw_get_driver();

	return drv->init(pin, mode);
}

int gpio_set_pin_mode(const uint8_t pin, const enum gpio_mode mode)
{
	const struct gpio_driver_api *drv = gpio_hw_get_driver();

	return drv->set_mode(pin, mode);
}

int gpio_set_state(const uint8_t pin, const bool state)
{
	const struct gpio_driver_api *drv = gpio_hw_get_driver();

	return drv->set_state(pin, state);
}

int gpio_get_state(const uint8_t pin)
{
	const struct gpio_driver_api *drv = gpio_hw_get_driver();

	return drv->get_state(pin);
}

int gpio_state_toggle(const uint8_t pin)
{
	const struct gpio_driver_api *drv = gpio_hw_get_driver();

	return drv->toggle(pin);
}

int gpio_set_state_mask(const uint8_t gpio_port, const uint32_t pin_mask,
			const uint32_t state_mask)
{
	const struct gpio_driver_api *drv = gpio_hw_get_driver();

	return drv->set_state_mask(gpio_port, pin_mask, state_mask);
}

int32_t gpio_get_state_mask(const uint8_t gpio_port, const uint32_t pin_mask)
{
	const struct gpio_driver_api *drv = gpio_hw_get_driver();

	return drv->get_state_mask(gpio_port, pin_mask);
}

int64_t gpio_convert_port_to_pin_num(const uint8_t gpio_port, const uint8_t port_pin)
{
	const struct gpio_driver_api *drv = gpio_hw_get_driver();

	return drv->convert_port_to_pin_num(gpio_port, port_pin);
}

/** \} End of gpio group */
