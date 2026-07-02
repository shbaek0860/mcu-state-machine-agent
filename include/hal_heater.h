#ifndef HAL_HEATER_H
#define HAL_HEATER_H

#include <stdint.h>
#include <stdio.h>

// 하드웨어 초기화 (설정 등)
static inline void HAL_Heater_Init(void) {
    printf("[HAL] Heater Hardware Initialized.\n");
}

// 기술적 의도: 빈번히 호출되는 하드웨어 주변장치 제어 함수는 MCU 스택 오버헤드 방지 및 실행 속도 최적화를 위해 inline 적용
static inline void HAL_Heater_SetPWM(uint8_t duty_cycle) {
    printf("[HAL] Setting Heater PWM to %d%%\n", duty_cycle);
}

// 기술적 의도: 아날로그 센서 값을 읽어오는 동작도 inline으로 최적화
static inline uint16_t HAL_Heater_ReadTemperature(void) {
    // 임베디드 ADC 모의 반환값
    return 25; 
}

#endif // HAL_HEATER_H
