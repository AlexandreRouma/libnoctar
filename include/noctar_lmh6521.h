#pragma once
#include <noctar.h>

#define NOCTAR_LMH6521_CMD_LEN      2
#define NOCTAR_LMH6521_CHAN_A_ADDR  0
#define NOCTAR_LMH6521_CHAN_B_ADDR  1
#define NOCTAR_LMH6521_MIN_GAIN     0.0f
#define NOCTAR_LMH6521_MAX_GAIN     31.5f

enum noctar_lmh6521_channel {
    NOCTAR_LMH6521_CHANNEL_A    = 0,
    NOCTAR_LMH6521_CHANNEL_B    = 1,
};
typedef enum noctar_lmh6521_channel noctar_lmh6521_channel_t;

/**
 * Write data into a register.
 * @param dev Noctar device instance.
 * @param addr Register address.
 * @param value Data to be written into the register.
 * @return NOCTAR_SUCCESS (0) on success.
 */
NOCTAR_EXPORT int noctar_lmh6521_write_reg(noctar_t* dev, uint8_t addr, uint8_t value);

/**
 * Set the gain of one or both channels.
 * @param dev Noctar device instance.
 * @param channel Channel(s) to configure.
 * @param gain Gain to set. Must be within NOCTAR_LMH6521_MIN_GAIN and NOCTAR_LMH6521_MAX_GAIN.
 */
NOCTAR_EXPORT int noctar_lmh6521_set_gain(noctar_t* dev, noctar_lmh6521_channel_t channel, float gain);