#include "event_queue.h"

static HeaterEvent_t queue[EVENT_QUEUE_SIZE];
static int head = 0;
static int tail = 0;

void EventQueue_Init(void) {
    head = 0;
    tail = 0;
}

// 기술적 의도: 인터럽트 발생 시 메인 루프로 이벤트를 안전하게 전달하기 위한 링버퍼 삽입
bool EventQueue_Push(HeaterEvent_t event) {
    int next = (head + 1) % EVENT_QUEUE_SIZE;
    if (next == tail) {
        return false; // Queue Full
    }
    queue[head] = event;
    head = next;
    return true;
}

// 기술적 의도: 메인 루프에서 순차적으로 이벤트를 처리하기 위한 팝
bool EventQueue_Pop(HeaterEvent_t* out_event) {
    if (head == tail) {
        return false; // Queue Empty
    }
    *out_event = queue[tail];
    tail = (tail + 1) % EVENT_QUEUE_SIZE;
    return true;
}

bool EventQueue_IsEmpty(void) {
    return (head == tail);
}
