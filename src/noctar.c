#include <noctar.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


NOCTAR_EXPORT int noctar_open(noctar_t** dev, const char* path) {
    // Check arguments
    if (!dev || !path) { return NOCTAR_ERROR_INVALID_ARGUMENT; }

    // Allocate device
    noctar_t* _dev = calloc(1, sizeof(noctar_t));
    if (!_dev) { return NOCTAR_ERROR_ALLOCATION_FAILURE; }
    *dev = _dev;

    // Open device file
    _dev->fd = open(path, O_RDWR);
    if (_dev->fd < 0) { return NOCTAR_ERROR_NOT_FOUND; }

    // Initialize device
    noctar_set_path(_dev, NOCTAR_DIR_BOTH, NOCTAR_PATH_LF);
    noctar_set_hf_gain(_dev, NOCTAR_DIR_BOTH, 0);
    noctar_set_resampling_stages(_dev, NOCTAR_DIR_BOTH, 0);
    // TODO: Rest of the init
    noctar_set_pin(_dev, IOCTL_SET_RXPhase, 0);

    return NOCTAR_SUCCESS;
}

NOCTAR_EXPORT void noctar_close(noctar_t* dev) {
    // Close device file
    close(dev->fd);

    // Free device
    free(dev);
}

NOCTAR_EXPORT int noctar_set_path(noctar_t* dev, noctar_direction_t dir, noctar_path_t path) {
    if (dir & NOCTAR_DIR_RX) {
        int err = noctar_set_pin(dev, IOCTL_SET_NASRxA, path);
        if (err) { return err; }
    }
    if (dir & NOCTAR_DIR_TX) {
        int err = noctar_set_pin(dev, IOCTL_SET_NASTxA, path);
        if (err) { return err; }
    }
    return NOCTAR_SUCCESS;
}

NOCTAR_EXPORT int noctar_set_hf_gain(noctar_t* dev, noctar_direction_t dir, uint8_t gain) {
    if (dir & NOCTAR_DIR_RX) {
        int err = noctar_set_pin(dev, IOCTL_SET_N21at0, gain);
        if (err) { return err; }
    }
    if (dir & NOCTAR_DIR_TX) {
        int err = noctar_set_pin(dev, IOCTL_SET_N22at0, gain);
        if (err) { return err; }
    }
    return NOCTAR_SUCCESS;
}

NOCTAR_EXPORT int noctar_set_resampling_stages(noctar_t* dev, noctar_direction_t dir, int stages) {
    // Check arguments
    if (stages < 0 || stages > NOCTAR_MAX_RESAMP_STAGES) { return NOCTAR_ERROR_INVALID_ARGUMENT; }

    // Apply setting
    if (dir & NOCTAR_DIR_RX) {
        int err = noctar_set_pin(dev, IOCTL_SET_RXDecEn, (1 << stages) - 1);
        if (err) { return err; }
    }
    if (dir & NOCTAR_DIR_TX) {
        int err = noctar_set_pin(dev, IOCTL_SET_TXIntEn, (1 << stages) - 1);
        if (err) { return err; }
    }
    return NOCTAR_SUCCESS;
}