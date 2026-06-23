/*
 * tps2044.c
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
 * \brief tps2044 device implementation.
 *
 * \author Carlos Augusto Porto Freitas <carlos.portof@hotmail.com>
 *
 * \version 0.2.10
 *
 * \date 2025/01/12
 *
 * \addtogroup tps2044
 * \{
 */

#include <stdbool.h>
#include <config/errno.h>
#include <system/sys_log/sys_log.h>
#include <drivers/gpio/gpio.h>

#include "tps2044.h"

#define IMAGE_SENSOR_EN_PIN (16U) /* PB0 (GPIO_PORT_B PIN0) */
#define IMAGE_SENSOR_CHANNEL (TPS_2044_CHANNEL_1)

/**
 * \brief Image sensor power supply switch instance.
 */
static tps_2044_t image_sensor_power_switch;

int tps2044_init(const tps_2044_t *dev)
{
	int err = 0;

	if (dev->en_mask & TPS_2044_USE_EN1) {
		if (gpio_init_pin(dev->en1_pin, GPIO_DRV_MODE_OUTPUT_PUSH_PULL) == 0) {
			/* This call cannot fail, if initialization suceeded */
			(void)gpio_set_state(dev->en1_pin, GPIO_STATE_LOW);
		} else {
			sys_log_print_event_from_module(
				SYS_LOG_ERROR, TPS_2044_MODULE_NAME,
				"Failed to initialized gpio pin for channel 1!");
			sys_log_new_line();
			err--;
		}
	}

	if (dev->en_mask & TPS_2044_USE_EN2) {
		if (gpio_init_pin(dev->en2_pin, GPIO_DRV_MODE_OUTPUT_PUSH_PULL) == 0) {
			/* This call cannot fail, if initialization suceeded */
			(void)gpio_set_state(dev->en1_pin, GPIO_STATE_LOW);
		} else {
			sys_log_print_event_from_module(
				SYS_LOG_ERROR, TPS_2044_MODULE_NAME,
				"Failed to initialized gpio pin for channel 2");
			sys_log_new_line();
			err--;
		}
	}

	if (err < 0) {
		err = -ERRNO_DEVICE_FAILED_CONFIG;
	}

	return err;
}

int tps2044_channel_enable(const tps_2044_t *dev, const tps_2044_channel_e channel)
{
	int err = -1;

	if (dev->en_mask & channel) {
		const uint8_t pin = (channel == TPS_2044_CHANNEL_1) ? dev->en1_pin : dev->en2_pin;
		err = gpio_set_state(pin, GPIO_STATE_HIGH);
	}

	return err;
}

int tps2044_channel_disable(const tps_2044_t *dev, const tps_2044_channel_e channel)
{
	int err = -1;

	if (dev->en_mask & channel) {
		const uint8_t pin = (channel == TPS_2044_CHANNEL_1) ? dev->en1_pin : dev->en2_pin;
		err = gpio_set_state(pin, GPIO_STATE_LOW);
	}

	return err;
}

bool is_tps2044_channel_enable(const tps_2044_t *dev, const tps_2044_channel_e channel)
{
	int err = -1;
	bool retval = false;

	if (dev->en_mask & channel) {
		const uint8_t pin = (channel == TPS_2044_CHANNEL_1) ? dev->en1_pin : dev->en2_pin;
		err = gpio_get_state(pin);

		if (err < 0) {
			sys_log_print_event_from_module(
				SYS_LOG_ERROR, TPS_2044_MODULE_NAME,
				"Failed to read tps2044 channel state! Errno: ");
			sys_log_print_msg(errno_to_string(err));
			sys_log_new_line();
		}
	}

	return retval;
}

int image_sensor_supply_switch_init(void)
{
	image_sensor_power_switch.en_mask = TPS_2044_USE_EN1;
	image_sensor_power_switch.en1_pin = IMAGE_SENSOR_EN_PIN;

	return tps2044_init(&image_sensor_power_switch);
}

int enable_image_sensor_supply(void)
{
	return tps2044_channel_enable(&image_sensor_power_switch, IMAGE_SENSOR_CHANNEL);
}

int disable_image_sensor_supply(void)
{
	return tps2044_channel_disable(&image_sensor_power_switch, IMAGE_SENSOR_CHANNEL);
}

bool is_image_sensor_power_supply_enabled(void)
{
	return is_tps2044_channel_enable(&image_sensor_power_switch, IMAGE_SENSOR_CHANNEL);
}

/** \} End of tps2044 group */
