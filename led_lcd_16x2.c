/*
 * led_lcd_16x2.c
 *
 *  Created on: Nov 18, 2024
 *      Author: pc
 */

#include "led_lcd_16x2.h"
I2C_HandleTypeDef hi2c1;

uint8_t HeartChar[] = {0x00, 0x00, 0x0a, 0x15, 0x11, 0x0a, 0x04, 0x00};
uint8_t SmileyFaceChar[] = {0x00, 0x00, 0x0a, 0x00, 0x1f, 0x11, 0x0e, 0x00};







