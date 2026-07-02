#include <stdio.h>
#include <unistd.h>
#include "heater_fsm.h"

// 전역 상태 머신 컨텍스트
HeaterContext_t g_heater_ctx;

// ISR 이벤트 큐 모의 변수
volatile HeaterEvent_t g_isr_event = EVENT_NONE;

// 모의 타이머 인터럽트 서비스 루틴
void Timer_ISR_Mock(void) {
    // [주의] 예외 및 취약점 방지: 
    // 모든 타이머 및 인터럽트 서비스 루틴(ISR) 내에서는 자원 경합(Race Condition) 가능성이 있습니다.
    // g_isr_event 변수에 대한 접근은 원자적(Atomic) 연산으로 처리되어야 안전합니다.
    g_isr_event = EVENT_OVERHEAT; 
}

int main(void) {
    printf("Starting MCU State Machine Agent...\n");
    
    // 1. 상태 머신 초기화
    HeaterFSM_Init(&g_heater_ctx);
    
    // [시나리오 1] 정상 작동 사이클
    printf("\n--- [Scenario 1] Normal Operation Cycle ---\n");
    printf("-> Sending EVENT_START\n");
    HeaterFSM_ProcessEvent(&g_heater_ctx, EVENT_START);
    
    printf("-> Sending EVENT_TEMP_REACHED\n");
    HeaterFSM_ProcessEvent(&g_heater_ctx, EVENT_TEMP_REACHED);
    
    printf("-> Sending EVENT_STOP\n");
    HeaterFSM_ProcessEvent(&g_heater_ctx, EVENT_STOP);

    // [시나리오 2] 인터럽트/에러 발생 사이클
    printf("\n--- [Scenario 2] ISR Error Handling ---\n");
    printf("-> Sending EVENT_START\n");
    HeaterFSM_ProcessEvent(&g_heater_ctx, EVENT_START);
    
    printf("-> Hardware Triggering Timer_ISR_Mock (Overheat)\n");
    Timer_ISR_Mock();
    
    // 메인 루프에서 ISR 이벤트 처리 (실제 환경에서는 인터럽트 플래그 확인)
    if (g_isr_event != EVENT_NONE) {
        printf("-> Processing ISR Event: %d\n", g_isr_event);
        HeaterFSM_ProcessEvent(&g_heater_ctx, g_isr_event);
        
        // 경합을 방지하기 위해 인터럽트 비활성화 블록 내부에서 초기화가 권장됨
        g_isr_event = EVENT_NONE;
    }
    
    // 최종 상태 출력 (STATE_ERROR 이어야 함)
    printf("-> Final State: %d (Expected: %d)\n", g_heater_ctx.current_state, STATE_ERROR);
    
    return 0;
}
