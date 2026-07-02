#include "heater_fsm.h"
#include "hal_heater.h"

void HeaterFSM_Init(HeaterContext_t* ctx) {
    if (!ctx) return;
    
    ctx->current_state = STATE_IDLE;
    ctx->current_temp = HAL_Heater_ReadTemperature();
    ctx->target_temp = 100; // 기본 목표 온도 설정
    
    HAL_Heater_SetPWM(0);
}

// 상태 전이 논리 처리 함수
void HeaterFSM_ProcessEvent(HeaterContext_t* ctx, HeaterEvent_t event) {
    if (!ctx) return;

    // 대규모 상태 머신 switch-case문은 100줄 예외 규칙 적용
    switch(ctx->current_state) {
        case STATE_IDLE:
            if (event == EVENT_START) {
                ctx->current_state = STATE_HEATING;
                HAL_Heater_SetPWM(100);
            }
            break;

        case STATE_HEATING:
            if (event == EVENT_OVERHEAT) {
                ctx->current_state = STATE_ERROR;
                HAL_Heater_SetPWM(0);
            } else if (event == EVENT_TEMP_REACHED) {
                ctx->current_state = STATE_COOLING;
                HAL_Heater_SetPWM(0);
            } else if (event == EVENT_STOP) {
                ctx->current_state = STATE_IDLE;
                HAL_Heater_SetPWM(0);
            }
            break;

        case STATE_COOLING:
            if (event == EVENT_START) {
                ctx->current_state = STATE_HEATING;
                HAL_Heater_SetPWM(100);
            } else if (event == EVENT_STOP) {
                ctx->current_state = STATE_IDLE;
                HAL_Heater_SetPWM(0);
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
            HAL_Heater_SetPWM(0);
            break;
    }
}
