/*
 * led_rgb.c
 *
 *  Created on: Nov 18, 2024
 *      Author: pc
 */

#include "led_grb.h"

#define LED_COUNT 1 // Số lượng LED
#define HIGH_TIME 60 // Tín hiệu PWM "1" (tùy chỉnh dựa vào WS2812)
#define LOW_TIME 30  // Tín hiệu PWM "0" (tùy chỉnh dựa vào WS2812)

uint8_t LED_Data[LED_COUNT][3];       // Dữ liệu LED [LED][R, G, B]
uint16_t PWM_Data[24 * LED_COUNT + 50]; // Tín hiệu PWM cho WS2812B
TIM_HandleTypeDef htim2;
// Hàm set màu cho từng LED
void Set_LED_Color(uint8_t led, uint8_t red, uint8_t green, uint8_t blue) {
    if (led < LED_COUNT) {
        LED_Data[led][0] = green;
        LED_Data[led][1] = red;
        LED_Data[led][2] = blue;
    }
}

// Chuyển đổi dữ liệu LED thành tín hiệu PWM
void WS2812_Update() {
    uint16_t pwm_index = 0;

    for (int i = 0; i < LED_COUNT; i++) {
        for (int j = 0; j < 24; j++) {
            if (LED_Data[i][j / 8] & (1 << (7 - (j % 8)))) {
                PWM_Data[pwm_index] = HIGH_TIME; // Ghi mức cao
            } else {
                PWM_Data[pwm_index] = LOW_TIME;  // Ghi mức thấp
            }
            pwm_index++;
        }
    }

    // Dữ liệu "reset" ở cuối
    // đếm đến 50 vì quy định để xem là đã đọc
    for (int i = 0; i < 50; i++) {
        PWM_Data[pwm_index++] = 0;
    }

    // Xuất tín hiệu qua PWM bằng DMA
    HAL_TIM_PWM_Start_DMA(&htim2, TIM_CHANNEL_1, (uint32_t *)PWM_Data, pwm_index);
}

// Hàm đổi màu theo nhiệt độ
void Update_Color_By_Temperature(uint8_t temperature) {
    uint8_t red = 0, green = 0, blue = 0;

    if (temperature <= 25) {
        // Lạnh -> màu xanh dương
        blue = 255 - (temperature * 10);
        green = temperature * 10;
    } else if (temperature <= 50) {
        // Nhiệt độ trung bình -> trộn xanh lá và đỏ
        green = 255 - ((temperature - 25) * 10);
        red = (temperature - 25) * 10;
    } else {
        // Nóng -> màu đỏ
        red = 255 - ((temperature - 50) * 10);
        blue = (temperature - 50) * 5;
    }

    // Cập nhật màu LED
    Set_LED_Color(0, red, green, blue);

    // Gửi tín hiệu PWM
    WS2812_Update();
}

//int main(void) {
//    // Khởi tạo phần cứng
//    HAL_Init();
//    MX_GPIO_Init();
//    MX_TIM1_Init();
//    MX_ADC1_Init();
//
//    // Bắt đầu PWM
//    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
//
//    uint8_t temperature = 0;
//
//    while (1) {
//        // Đọc nhiệt độ từ ADC hoặc cảm biến
//        temperature = GetTemperature(); // Hàm giả lập giá trị 0–75°C
//
//        // Cập nhật màu LED theo nhiệt độ
//        Update_Color_By_Temperature(temperature);
//
//        HAL_Delay(100); // Đợi để cập nhật LED
//    }
//}

// Hàm giả lập nhiệt độ (hoặc thay bằng hàm đọc thực từ ADC)
//uint8_t GetTemperature(void) {
//    uint32_t adc_value = HAL_ADC_GetValue(&hadc1); // Đọc giá trị từ ADC
//    uint8_t temperature = (adc_value * 75) / 4095; // Chuyển đổi ADC (0-4095) sang nhiệt độ (0-75°C)
//    return temperature;
//}


