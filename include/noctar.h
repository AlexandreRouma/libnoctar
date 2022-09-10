#pragma once
#include <stdint.h>
#include <stdbool.h>

// Make sure the symbols are not mangled
#ifdef __cplusplus
extern "C" {
#endif

// Shared lib export definition
#ifdef _MSC_VER
#define NOCTAR_EXPORT   __declspec(dllexport)
#else
#define NOCTAR_EXPORT   __attribute__((visibility("default")))
#endif

// TODO: Find the actual value in the manual
#define NOCTAR_MAX_RESAMP_STAGES    8

#define NOCTAR_MIN_HF_GAIN          0.0f
#define NOCTAR_MAX_HF_GAIN          30.0f
#define NOCTAR_MIN_RX_HF_VGA_GAIN   0.0f
#define NOCTAR_MAX_RX_HF_VGA_GAIN   31.5f

enum noctar_error {
    NOCTAR_SUCCESS                  = 0,

    NOCTAR_ERROR_INVALID_ARGUMENT   = -1,
    NOCTAR_ERROR_ALLOCATION_FAILURE = -2,
    NOCTAR_ERROR_NOT_FOUND          = -3,

    NOCTAR_ERROR_UNSUPPORTED        = -9999
};

enum noctar_direction {
    NOCTAR_DIR_RX       = (1 << 0),
    NOCTAR_DIR_TX       = (1 << 1),
    NOCTAR_DIR_BOTH     = NOCTAR_DIR_RX | NOCTAR_DIR_TX
};
typedef enum noctar_direction noctar_direction_t;

enum noctar_path {
    NOCTAR_PATH_HF,
    NOCTAR_PATH_LF
};
typedef enum noctar_path noctar_path_t;

enum noctar_adc {
    NOCTAR_ADC_A    = (1 << 0),
    NOCTAR_ADC_B    = (1 << 1),
    NOCTAR_ADC_BOTH = NOCTAR_ADC_A | NOCTAR_ADC_B
};
typedef enum noctar_adc noctar_adc_t;

struct noctar {
    int fd;
};
typedef struct noctar noctar_t;

/**
 * Open a noctar device from its device file.
 * @param dev Pointer to a noctar_t pointer to be initialized when the device is open.
 * @param path Path to the device file. Usually /dev/langford.
 * @return NOCTAR_SUCCESS (0) on success.
 */
NOCTAR_EXPORT int noctar_open(noctar_t** dev, const char* path);

/**
 * Close a noctar device.
 * @param dev noctar_t pointer to be closed and freed.
 */
NOCTAR_EXPORT void noctar_close(noctar_t* dev);

/**
 * Chose which signal path to send to the ADC/DAC.
 * @param dev Noctar device instance.
 * @param dir RF direction, either NOCTAR_DIR_RX or NOCTAR_DIR_TX
 * @param path RF path to chose, either NOCTAR_PATH_LF for DC to 60MHz or NOCTAR_PATH_HF for 35MHz to 4.5GHz.
 * @return NOCTAR_SUCCESS (0) on success.
 */
NOCTAR_EXPORT int noctar_set_path(noctar_t* dev, noctar_direction_t dir, noctar_path_t path);

/**
 * Set gain of the high frequency RF path by controlling the RFSA2013 variable attenuator.
 * @param dev Noctar device instance.
 * @param dir RF direction, either NOCTAR_DIR_RX or NOCTAR_DIR_TX
 * @param gain Gain in dB. Must be between 0 and 30dB.
 * @return NOCTAR_SUCCESS (0) on success.
 */
NOCTAR_EXPORT int noctar_set_hf_gain(noctar_t* dev, noctar_direction_t dir, float gain);

/**
 * Set gain of the RX high frequency ADC variable gain amplifier.
 * @param dev Noctar device instance.
 * @param adc Which ADC to apply the gain to.
 * @param gain Gain between 0 and 31.5dB.
 * @return NOCTAR_SUCCESS (0) on success.
 */
NOCTAR_EXPORT int noctar_set_rx_hf_vga_gain(noctar_t* dev, noctar_adc_t adc, float gain);

/**
 * Set the number of half band decimation or interpolation stages. (TODO: Switch to set_rx_decimation / set_tx_interpolation instead)
 * @param dev Noctar device instance.
 * @param dir RF direction, either NOCTAR_DIR_RX or NOCTAR_DIR_TX.
 * @param stages Number of stages.
 * @return NOCTAR_SUCCESS (0) on success.
 */
NOCTAR_EXPORT int noctar_set_resampling_stages(noctar_t* dev, noctar_direction_t dir, int stages);

// Include the rest of the API
#include <noctar_io.h>
#include <noctar_lmh6521.h>
#include <noctar_spi.h>

// End of extern "C"
#ifdef __cplusplus
}
#endif