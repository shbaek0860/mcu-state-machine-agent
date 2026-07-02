#include <stdio.h>
#include "timer_isr.h"
#include "event_queue.h"

void Timer_ISR_Init(void) {
    printf("[ISR] Timer Interrupt Service Routine Initialized.\n");
}

void Timer_ISR_Trigger(void) {
    // 주의: 인터럽트 서비스 루틴(ISR) 내에서는 자원 경합(Race Condition)을 방지하기 위해 
    // 직접 전역 변수나 FSM을 호출하지 않고 Event Queue에 이벤트를 삽입하는 방식으로 안전하게 처리함.
    printf("[ISR] Hardware Interrupt Occurred: OVERHEAT detected!\n");
    EventQueue_Push(EVENT_OVERHEAT);
}
