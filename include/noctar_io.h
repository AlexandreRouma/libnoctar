#pragma once
#include <noctar.h>
#include <langford_ioctl.h>

/**
 * Get the value of a pin.
 * @param dev Noctar device instance.
 * @param pin ID of the pin.
 * @param value Pointer to write the value to.
 * @return NOCTAR_SUCCESS (0) on success.
 */
NOCTAR_EXPORT int noctar_get_pin(noctar_t* dev, int pin, uint64_t* value);

/**
 * Set the value of a pin.
 * @param dev Noctar device instance.
 * @param pin ID of the pin.
 * @param value Value to write.
 * @return NOCTAR_SUCCESS (0) on success.
 */
NOCTAR_EXPORT int noctar_set_pin(noctar_t* dev, int pin, uint64_t value);

/**
 * Read samples from the device.
 * @param dev Noctar device instance.
 * @param data int16 buffer to write the samples into.
 * @param len Number of samples to read.
 * @return NOCTAR_SUCCESS (0) on success.
 */
NOCTAR_EXPORT int noctar_rx_sync(noctar_t* dev, int16_t* data, int len);

/**
 * Write samples to the device.
 * @param dev Noctar device instance.
 * @param data int16 buffer of samples to be written
 * @param len Number of samples to write.
 * @return NOCTAR_SUCCESS (0) on success.
 */
NOCTAR_EXPORT int noctar_tx_sync(noctar_t* dev, const int16_t* data, int len);