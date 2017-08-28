#ifndef IR_THERMO_PIN_CONFIG_H
#define IR_THERMO_PIN_CONFIG_H

#include <Arduino.h>

// PINS
#define SPI_CLOCK 13 //SCLK
#define SPI_DATA 11
#define SPI_DC 9
#define SPI_RESET 8

#define SPI_CS_DISPLAY 6
#define SPI_CS_ATMEGA328 10
#define SPI_CS_SD 7

#define PISTOL_TRIGGER_PIN A0
#define LASER_INPUT_PIN A1
#define BACKGROUND_LIGHT_INPUT_PIN A2
#define LASER_OUTPUT_PIN 3
#define BACKGROUND_LIGHT_OUTPUT_PIN 2

#define CONTINUOUS_MEASUREMENT_INTERVAL_SECS 5

#endif //IR_THERMO_PIN_CONFIG_H
