#ifndef HEATER_FSM_H
#define HEATER_FSM_H

#include <stdint.h>
#include <stdbool.h>

// 상태 머신 상태 정의
typedef enum {
    STATE_IDLE,
    STATE_HEATING,
    STATE_COOLING,
    STATE_ERROR
} HeaterState_t;

// 상태 머신 이벤트 정의
typedef enum {
    EVENT_START,
    EVENT_STOP,
    EVENT_TEMP_REACHED,
    EVENT_OVERHEAT,
    EVENT_NONE
} HeaterEvent_t;

// 상태 머신 컨텍스트
typedef struct {
    HeaterState_t current_state;
    uint16_t current_temp;
    uint16_t target_temp;
} HeaterContext_t;

// 인터페이스 함수
void HeaterFSM_Init(HeaterContext_t* ctx);
void HeaterFSM_ProcessEvent(HeaterContext_t* ctx, HeaterEvent_t event);

#endif // HEATER_FSM_H
