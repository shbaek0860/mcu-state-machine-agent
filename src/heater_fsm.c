#include "heater_fsm.h"
#include <stdio.h>

// 하드웨어 제어 함수들 (단일 책임 원칙 준수)
// 기술적 의도: 하드웨어 주변장치 제어 시 MCU 스택 오버헤드 방지 및 실행 속도 최적화를 위해 inline 사용
static inline void HW_SetHeaterPWM(uint8_t duty_cycle) {
    printf("[HW] Setting Heater PWM to %d%%\n", duty_cycle);
}

static inline uint16_t HW_ReadTemperature(void) {
    // 모의 온도 반환
    return 25; 
}

void HeaterFSM_Init(HeaterContext_t* ctx) {
    if (!ctx) return;
    
    ctx->current_state = STATE_IDLE;
    ctx->current_temp = HW_ReadTemperature();
    ctx->target_temp = 100; // 기본 목표 온도 설정
    
    HW_SetHeaterPWM(0);
}

// 상태 전이 논리 처리 함수
void HeaterFSM_ProcessEvent(HeaterContext_t* ctx, HeaterEvent_t event) {
    if (!ctx) return;

    // 대규모 상태 머신 switch-case문은 100줄 예외 규칙 적용
    switch(ctx->current_state) {
        case STATE_IDLE:
            if (event == EVENT_START) {
                ctx->current_state = STATE_HEATING;
                HW_SetHeaterPWM(100);
            }
            break;

        case STATE_HEATING:
            if (event == EVENT_OVERHEAT) {
                ctx->current_state = STATE_ERROR;
                HW_SetHeaterPWM(0);
            } else if (event == EVENT_TEMP_REACHED) {
                ctx->current_state = STATE_COOLING;
                HW_SetHeaterPWM(0);
            } else if (event == EVENT_STOP) {
                ctx->current_state = STATE_IDLE;
                HW_SetHeaterPWM(0);
            }
            break;

        case STATE_COOLING:
            if (event == EVENT_START) {
                ctx->current_state = STATE_HEATING;
                HW_SetHeaterPWM(100);
            } else if (event == EVENT_STOP) {
                ctx->current_state = STATE_IDLE;
                HW_SetHeaterPWM(0);
            }
            break;

        case STATE_ERROR:
            // 에러 상태에서는 STOP 이벤트 발생 시에만 초기화 가능
            if (event == EVENT_STOP) {
                ctx->current_state = STATE_IDLE;
            }
            break;
            
        default:
            ctx->current_state = STATE_ERROR;
            HW_SetHeaterPWM(0);
            break;
    }
}
