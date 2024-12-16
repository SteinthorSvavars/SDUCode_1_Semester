#ifndef ADCPWM_H_INCLUDED
#define ADCPWM_H_INCLUDED

#include <stdint.h>

/**
 * @brief Initialises the ADC module
 **/
void adc_initSES(void);

/**
 * @brief Reads the voltage provided at the input channel and returns the adc value as 10 bit
 * @param[in] channel input ADC channel [0-5] corresponding to inputs PC0..PC5
 * @param[out] result 10bit analog to digital conversion result in range [0-1023]
 * @note The corresponding input needs to be configured externally as input in the DDRC register and pullups enabled/disabled if necessary in PORTC
 **/
uint16_t adc_readSES(uint8_t channel);

#endif