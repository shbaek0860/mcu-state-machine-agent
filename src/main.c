#include <stdio.h>
#include <unistd.h>
#include "hal_heater.h"
#include "heater_fsm.h"
#include "event_queue.h"
#include "timer_isr.h"

// 전역 상태 머신 컨텍스트
HeaterContext_t g_heater_ctx;

int main(void) {
    printf("Starting Modular MCU State Machine Agent...\n\n");
    
    // 1. 하위 모듈 초기화
    HAL_Heater_Init();
    EventQueue_Init();
    Timer_ISR_Init();
    HeaterFSM_Init(&g_heater_ctx);
    
    // 모의 환경: 펌웨어 수퍼루프에 들어가기 전 시나리오 이벤트를 순차적으로 큐에 넣음.
    printf("\n--- [Scenario Injection] ---\n");
    EventQueue_Push(EVENT_START);
    EventQueue_Push(EVENT_TEMP_REACHED);
    EventQueue_Push(EVENT_STOP);
    
    // 에러 시나리오
    EventQueue_Push(EVENT_START);
    // ISR이 직접 이벤트 큐에 OVERHEAT 이벤트를 넣도록 트리거
    Timer_ISR_Trigger(); 
    
    printf("\n--- [Entering Super Loop] ---\n");
    
    // 2. 펌웨어 메인 수퍼 루프 (Super Loop)
    int max_loops = 10; // 테스트를 위해 무한루프 방지
    while (max_loops--) {
        HeaterEvent_t evt;
        
        // 이벤트 큐 폴링 (Polling)
        if (!EventQueue_IsEmpty()) {
            if (EventQueue_Pop(&evt)) {
                printf("[Main Loop] Processing Event: %d\n", evt);
                HeaterFSM_ProcessEvent(&g_heater_ctx, evt);
            }
        } else {
            // 처리할 이벤트가 없으면 대기 (Sleep or WFI)
            printf("[Main Loop] No more events. Idle.\n");
            break;
        }
    }
    
    printf("\n-> Final State: %d (Expected: %d)\n", g_heater_ctx.current_state, STATE_ERROR);
    
    return 0;
}
