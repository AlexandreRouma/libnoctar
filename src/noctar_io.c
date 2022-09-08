#include <noctar_io.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

NOCTAR_EXPORT int noctar_get_pin(noctar_t* dev, int pin, uint64_t* value) {
    return ioctl(dev->fd, pin, value);
}

NOCTAR_EXPORT int noctar_set_pin(noctar_t* dev, int pin, uint64_t value) {
    return ioctl(dev->fd, pin, &value);
}

NOCTAR_EXPORT int noctar_rx_sync(noctar_t* dev, int16_t* data, int len) {
    return read(dev->fd, data, len * sizeof(int16_t));
}

NOCTAR_EXPORT int noctar_tx_sync(noctar_t* dev, const int16_t* data, int len) {
    return write(dev->fd, data, len * sizeof(int16_t));
}