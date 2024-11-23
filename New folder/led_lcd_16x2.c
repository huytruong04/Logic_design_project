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


//void LCD_InitializeAndDisplay() {
//    I2C_LCD_Init(MyI2C_LCD);
//    I2C_LCD_CreateCustomChar(MyI2C_LCD, 0, HeartChar);
//    I2C_LCD_CreateCustomChar(MyI2C_LCD, 1, SmileyFaceChar);
//    I2C_LCD_SetCursor(MyI2C_LCD, 0, 0);
//    I2C_LCD_WriteString(MyI2C_LCD, "DeepBlueMbedded");
//    I2C_LCD_SetCursor(MyI2C_LCD, 0, 1);
//    I2C_LCD_WriteString(MyI2C_LCD, "I2C LCD ");
//    I2C_LCD_PrintCustomChar(MyI2C_LCD, 1);
//    I2C_LCD_PrintCustomChar(MyI2C_LCD, 0);
//}

//void LCD_InitializeAndDisplay() {
//    // Khởi tạo LCD
//    I2C_LCD_Init(MyI2C_LCD);
//    I2C_LCD_CreateCustomChar(MyI2C_LCD, 0, HeartChar);
//    I2C_LCD_CreateCustomChar(MyI2C_LCD, 1, SmileyFaceChar);
//    char buffer[30];
//    Status_Trigger_DHT20 check_sensor = trigger_measurement_data_dht20();
//    RH = RH * 100;
//    Temp = Temp * 100;
//    int humidity = (int)(RH);
//    int temp = (int)(Temp);
//
//    if (check_sensor == DHT20_OK) {
//        // Nếu đọc dữ liệu thành công
//    	sprintf(buffer, "Humidity: %d.%d", humidity / 100, humidity % 100);
//        I2C_LCD_SetCursor(MyI2C_LCD, 0, 0); // Đặt con trỏ dòng 0, cột 0
//        I2C_LCD_WriteString(MyI2C_LCD, buffer);
//
//        sprintf(buffer, "Temperature: %d.%d", temp / 100, temp % 100);
//        I2C_LCD_SetCursor(MyI2C_LCD, 1, 0); // Đặt con trỏ dòng 1, cột 0
//        I2C_LCD_WriteString(MyI2C_LCD, buffer);
//
//        HAL_Delay(700);
//    } else if (check_sensor == DHT20_BUSY) {
//        // Nếu cảm biến đang bận
//        sprintf(buffer, "Humidity:--BUSY--");
//        I2C_LCD_SetCursor(MyI2C_LCD, 0, 0);
//        I2C_LCD_WriteString(MyI2C_LCD, buffer);
//
//        sprintf(buffer, "Temperature:--BUSY--");
//        I2C_LCD_SetCursor(MyI2C_LCD, 1, 0);
//        I2C_LCD_WriteString(MyI2C_LCD, buffer);
//
//        HAL_Delay(1000);
//        I2C_LCD_Clear(MyI2C_LCD); // Xóa màn hình
//    } else {
//        // Nếu lỗi hoặc không có dữ liệu
//        sprintf(buffer, "Humidity:--NONE--");
//        I2C_LCD_SetCursor(MyI2C_LCD, 0, 0);
//        I2C_LCD_WriteString(MyI2C_LCD, buffer);
//
//        sprintf(buffer, "Temperature:--NONE--");
//        I2C_LCD_SetCursor(MyI2C_LCD, 1, 0);
//        I2C_LCD_WriteString(MyI2C_LCD, buffer);
//
//        HAL_Delay(1000);
//        I2C_LCD_Clear(MyI2C_LCD); // Xóa màn hình
//    }
//}

//void readSensorData() {
//    if (mySerial.available()) {
//        String data = "";
//        while (mySerial.available()) {
//            char c = mySerial.read();  // Đọc từng byte dữ liệu
//            data += c;
//        }
//
//        // Phân tích chuỗi dữ liệu nhận được
//        int tempIndex = data.indexOf("Temp:");
//        int humidityIndex = data.indexOf("Humidity:");
//
//        if (tempIndex != -1 && humidityIndex != -1) {
//            temperature = data.substring(tempIndex + 5, data.indexOf(' ', tempIndex)).toFloat();
//            humidity = data.substring(humidityIndex + 9).toFloat();
//        }
//    }
//}





//void LCD_DisplayTestSequence() {
//       I2C_LCD_NoBacklight(MyI2C_LCD);
//       HAL_Delay(1000);
//       I2C_LCD_Backlight(MyI2C_LCD);
//       HAL_Delay(1000);
//
//       I2C_LCD_ShiftRight(MyI2C_LCD);
//       HAL_Delay(500);
//       I2C_LCD_ShiftRight(MyI2C_LCD);
//       HAL_Delay(500);
//       I2C_LCD_ShiftRight(MyI2C_LCD);
//       HAL_Delay(500);
//
//       I2C_LCD_ShiftLeft(MyI2C_LCD);
//       HAL_Delay(500);
//       I2C_LCD_ShiftLeft(MyI2C_LCD);
//       HAL_Delay(500);
//       I2C_LCD_ShiftLeft(MyI2C_LCD);
//       HAL_Delay(500);
//
//       I2C_LCD_Cursor(MyI2C_LCD);
//       HAL_Delay(1000);
//       I2C_LCD_Blink(MyI2C_LCD);
//       HAL_Delay(2000);
//       I2C_LCD_NoBlink(MyI2C_LCD);
//       HAL_Delay(2000);
//
//       I2C_LCD_NoCursor(MyI2C_LCD);
//       HAL_Delay(1000);
//       I2C_LCD_NoDisplay(MyI2C_LCD);
//       HAL_Delay(1000);
//       I2C_LCD_Display(MyI2C_LCD);
//       HAL_Delay(1000);
//   }

//I2C_HandleTypeDef hi2c1;  // change your handler here accordingly
//
//#define SLAVE_ADDRESS_LCD 0x27 // change this according to ur setup


//
//void lcd_send_cmd (char cmd)
//{
//  char data_u, data_l;
//	uint8_t data_t[4];
//	data_u = (cmd&0xf0); /*higher nibble of data first*/
//	data_l = ((cmd<<4)&0xf0); /*lower nibble of data */
//	data_t[0] = data_u|0x0C;  //en=1, rs=0
//	data_t[1] = data_u|0x08;  //en=0, rs=0
//	data_t[2] = data_l|0x0C;  //en=1, rs=0
//	data_t[3] = data_l|0x08;  //en=0, rs=0
//	HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD << 1,(uint8_t *) data_t, 4, 100);
//}
//
//void lcd_send_data (char data)
//{
//	char data_u, data_l;
//	uint8_t data_t[4];
//	data_u = (data&0xf0);
//	data_l = ((data<<4)&0xf0);
//	data_t[0] = data_u|0x0D;  //en=1, rs=1
//	data_t[1] = data_u|0x09;  //en=0, rs=1
//	data_t[2] = data_l|0x0D;  //en=1, rs=1
//	data_t[3] = data_l|0x09;  //en=0, rs=1
//	HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD << 1,(uint8_t *) data_t, 4, 100);
//}
//
//void lcd_clear (void)
//{
//	lcd_send_cmd (0x80);
//	for (int i=0; i<70; i++)
//	{
//		lcd_send_data (' ');
//	}
//}
//
//void lcd_put_cur(int row, int col)
//{
//    switch (row)
//    {
//        case 0:
//            col |= 0x80;
//            break;
//        case 1:
//            col |= 0xC0;
//            break;
//				case 2:
//            col |= 0x94;
//            break;
//        case 3:
//            col |= 0xD4;
//            break;
//    }
//
//    lcd_send_cmd (col);
//}
//
//
//void lcd_init (void)
//{
//	// 4 bit initialisation
//	HAL_Delay(50);  // wait for >40ms
//	lcd_send_cmd (0x30);
//	HAL_Delay(5);  // wait for >4.1ms
//	lcd_send_cmd (0x30);
//	HAL_Delay(1);  // wait for >100us
//	lcd_send_cmd (0x30);
//	HAL_Delay(10);
//	lcd_send_cmd (0x20);  // 4bit mode
//	HAL_Delay(10);
//
//  // dislay initialisation
//	lcd_send_cmd (0x28); // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
//	HAL_Delay(1);
//	lcd_send_cmd (0x08); //Display on/off control --> D=0,C=0, B=0  ---> display off
//	HAL_Delay(1);
//	lcd_send_cmd (0x01);  // clear display
//	HAL_Delay(1);
//	HAL_Delay(1);
//	lcd_send_cmd (0x06); //Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
//	HAL_Delay(1);
//	lcd_send_cmd (0x0C); //Display on/off control --> D = 1, C and B = 0. (Cursor and blink, last two bits)
//	HAL_Delay(5);
//	lcd_clear();
//	HAL_Delay(100);
//}
//
//void lcd_send_string (char *str)
//{
//	while (*str) lcd_send_data (*str++);
//}
//
//void lcd_send_float(int integer_part, int fractional_part)
//{
//    // Gửi phần nguyên
//    lcd_send_data(integer_part + '0');
//    lcd_send_data('.');
//    // Gửi phần thập phân
//    lcd_send_data(fractional_part + '0');
//}




