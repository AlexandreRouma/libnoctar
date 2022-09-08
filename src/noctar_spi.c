#include <noctar_spi.h>

NOCTAR_EXPORT int noctar_spi_read(noctar_t* dev, int csPin, int clkPin, int dataPin, uint8_t* data, int len) {
    int err = 0;
    uint64_t value = 0;

    // Init IO pins
    err |= noctar_set_pin(dev, csPin, 1);
    err |= noctar_set_pin(dev, clkPin, 0);

    // Pull CS low to begin the transfer
    err |= noctar_set_pin(dev, csPin, 0);

    // Send data MSB first
    for (int i = 0; i < len * 8; i++) {
        // Zero out byte if first write
        if (!(i % 8)) { data[i / 8] = 0; }

        // Get data pin and add to data
        err |= noctar_get_pin(dev, dataPin, &value);
        data[i / 8] |= (value & 1) << (7 - (i % 8));

        // Pulse clock pin
        err |= noctar_set_pin(dev, clkPin, 1);
        err |= noctar_set_pin(dev, clkPin, 0);
    }

    // Pull CS high to end the transfer
    err |= noctar_set_pin(dev, csPin, 1);

    return err;
}

NOCTAR_EXPORT int noctar_spi_write(noctar_t* dev, int csPin, int clkPin, int dataPin, uint8_t* data, int len) {
    int err = 0;

    // Init IO pins
    err |= noctar_set_pin(dev, csPin, 1);
    err |= noctar_set_pin(dev, clkPin, 0);

    // Pull CS low to begin the transfer
    err |= noctar_set_pin(dev, csPin, 0);

    // Send data MSB first
    for (int i = 0; i < len * 8; i++) {
        // Set data pin
        err |= noctar_set_pin(dev, dataPin, (data[i / 8] >> (7 - (i % 8))) & 1);

        // Pulse clock pin
        err |= noctar_set_pin(dev, clkPin, 1);
        err |= noctar_set_pin(dev, clkPin, 0);
    }

    // Pull CS high to end the transfer
    err |= noctar_set_pin(dev, csPin, 1);

    return err;
}