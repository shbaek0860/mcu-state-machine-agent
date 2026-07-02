#ifndef TIMER_ISR_H
#define TIMER_ISR_H

void Timer_ISR_Init(void);

// 하드웨어 인터럽트 발생을 모의하기 위한 함수
void Timer_ISR_Trigger(void);

#endif // TIMER_ISR_H
