/*
 * tps2044.h
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
 * \brief tps2044 device definitions.
 *
 * \author Carlos Augusto Porto Freitas <carlos.portof@hotmail.com>
 *
 * \version 0.2.10
 *
 * \date 2025/01/12
 *
 * \defgroup tps2044 tps2044
 * \ingroup devices
 * \{
 */

#ifndef TPS_2044_H_
#define TPS_2044_H_

#include <stdbool.h>
#include <stdint.h>

#include <utils/macros/macros.h>

#define TPS_2044_MODULE_NAME "tps2044"

#define TPS_2044_USE_EN1 __BIT(0)
#define TPS_2044_USE_EN2 __BIT(1)

/**
 * \brief tps2044 channels enum
 */
typedef enum {
	TPS_2044_CHANNEL_1 = TPS_2044_USE_EN1,
	TPS_2044_CHANNEL_2 = TPS_2044_USE_EN2,
} tps_2044_channel_e;

/**
 * \brief tps2044 device struct.
 */
typedef struct {
	uint8_t en_mask; /**< Mask to determine which channels are enabled. Ex: If both channels are enabled en_mask should be set to (TPS_2044_USE_EN1 | TPS_2044_USE_EN2) */
	uint8_t en1_pin; /**< Channel 1 enable */
	uint8_t en2_pin; /**< Channel 2 enable */
} tps_2044_t;

/**
 * \brief Initializes the tps2044 switch. The switches is NOT enabled in initialization.
 *
 * \param[in] dev is the tps2044 device struct.
 *
 * \return The status/error code.
 */
int tps2044_init(const tps_2044_t *dev);

/**
 * \brief Enables the specified channel.
 *
 * \param[in] dev is the tps2044 device struct.
 *
 * \param[in] channel is the tps2044 channel to be enabled.
 *
 * \return The status/error code.
 */
int tps2044_channel_enable(const tps_2044_t *dev, const tps_2044_channel_e channel);

/**
 * \brief Disables the specified channel.
 *
 * \param[in] dev is the tps2044 device struct.
 *
 * \param[in] channel is the tps2044 channel to be disabled.
 *
 * \return The status/error code.
 */
int tps2044_channel_disable(const tps_2044_t *dev, const tps_2044_channel_e channel);

/**
 * \brief Checks if the specified sensor is enabled.
 *
 * \param[in] dev is the tps2044 device struct.
 *
 * \param[in] channel is the tps2044 channel to be disabled.
 *
 * \return True if the channel is enabled. False if it is disabled or the function errors.
 */
bool is_tps2044_channel_enable(const tps_2044_t *dev, const tps_2044_channel_e channel);

/**************************** Image Sensor Power Supply implementation ****************************/

/**
 * \brief Initializes image sensor power supply.
 *
 * \return The status/error code.
 */
int image_sensor_supply_switch_init(void);

/**
 * \brief Enables image sensor power supply.
 *
 * \return The status/error code.
 */
int enable_image_sensor_supply(void);

/**
 * \brief Disables image sensor power supply.
 *
 * \return The status/error code.
 */
int disable_image_sensor_supply(void);

/**
 * \brief Checks if the image sensor power supply is enabled.
 *
 * \return True if the power supply is enabled. False otherwise.
 */
bool is_image_sensor_power_supply_enabled(void);

#endif

/** \} End of tps2044 group */
