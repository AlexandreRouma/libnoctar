#include <noctar_lmh6521.h>
#include <noctar_spi.h>
#include <math.h>

NOCTAR_EXPORT int noctar_lmh6521_write_reg(noctar_t* dev, uint8_t addr, uint8_t value) {
    uint8_t data[NOCTAR_LMH6521_CMD_LEN] = { addr & 0b1111, value };
    return noctar_spi_write(dev, IOCTL_SET_N7CS, IOCTL_SET_N7CLK, IOCTL_SET_N7SDI, data, NOCTAR_LMH6521_CMD_LEN);
}

NOCTAR_EXPORT int noctar_lmh6521_set_gain(noctar_t* dev, noctar_lmh6521_channel_t channel, float gain) {
    // Check that requested gain is valid
    if (gain < NOCTAR_LMH6521_MIN_GAIN || gain > NOCTAR_LMH6521_MAX_GAIN) {
        return NOCTAR_ERROR_INVALID_ARGUMENT;
    }

    // Calculate binary value
    uint8_t attVal = 63 - roundf(2.0f * gain);

    // Set it
    noctar_lmh6521_write_reg(dev, channel, (1 << 7) | (attVal << 1));

    return NOCTAR_SUCCESS;
}