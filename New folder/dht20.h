/*
 * dht20.h
 *
 *  Created on: Nov 8, 2024
 *      Author: HPVictus
 */

#ifndef INC_DHT20_H_
#define INC_DHT20_H_

#include "main.h"  // Hoặc include đúng header cho MCU bạn đang dùng
#include <stdio.h>
#define ADDRESS_SLAVE_DHT20 0X38

// Khai báo các hàm và cấu trúc liên quan đến DHT20
typedef enum
{
  DHT20_OK			= 0x00U,
  DHT20_ERROR_INIT	= 0x01U,
  DHT20_ERROR_CRC	= 0x02U,
  DHT20_BUSY		= 0x03U
} Status_Trigger_DHT20;
I2C_HandleTypeDef hi2c1;
extern float RH;
extern float Temp;
Status_Trigger_DHT20 trigger_measurement_data_dht20();
unsigned char  CheckCrc8(unsigned char *pDat,unsigned char Lenth);
uint8_t read_register(uint8_t register_pointer);

#endif /* INC_DHT20_H_ */
