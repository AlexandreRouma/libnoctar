#pragma once
#include <noctar.h>

/**
 * Read a number of bytes MSB first from the specified data pins.
 * @param dev Noctar device instance.
 * @param csPin Chip select pîn.
 * @param clkPin SPI clock pin.
 * @param dataPin SPI data pin.
 * @param data Buffer of bytes in which to write the data read from the port.
 * @param len Number of bytes to be read from the port.
 * @return NOCTAR_SUCCESS (0) on success.
 */
NOCTAR_EXPORT int noctar_spi_read(noctar_t* dev, int csPin, int clkPin, int dataPin, uint8_t* data, int len);

/**
 * Write a number of bytes MSB first to the specified data pins.
 * @param dev Noctar device instance.
 * @param csPin Chip select pîn.
 * @param clkPin SPI clock pin.
 * @param dataPin SPI data pin.
 * @param data Buffer of bytes to be written to the port.
 * @param len Number of bytes to be written to the port.
 * @return NOCTAR_SUCCESS (0) on success.
 */
NOCTAR_EXPORT int noctar_spi_write(noctar_t* dev, int csPin, int clkPin, int dataPin, uint8_t* data, int len);