#ifndef MAIN_H
#define MAIN_H

#include "ses_led.h"
#include "ses_button.h"
#include "ses_common.h"
#include "ses_scheduler.h"
#include "ses_lcd.h"

//Enum to select LED color
typedef enum {
    RED=0,
    YELLOW,
    GREEN
}color;

/*FUNCTION PROTOTYPES*************************************************/

/**
 * Function to toggle the specified led using a color selected from enum @color
 * @param colorSelect ,void pointer to the color of LED
 */
void ledToggleTask (void* colorSelect);

/**
 * Function to debounce buttons
 */
void debounceButtonTask();

/**
 * Function to check if the joystick is pressed or not
 * conditions:
 * if pressed, yellow led is off
 * if not, yellow led is on
 */
void joystickPressed();

/**
 * Function to turn off the yellow led automatically if the joystick is pressed
 */
void turnYellowOff();

/**
 * Function to stop the stopwatch if the rotary button is pressed
 * otherwise, it starts the stopwatch
 */
void rotaryPressed();

/**
 * Function to increment the tenths of seconds until it overflows
 * then it increments the seconds and display both values on LCD
 */
void stopwatchOn();

/**
 * Function to automatically display the seconds and tenths values on LCD
 */
void LCDprint(uint8_t s, uint8_t t);

#endif
