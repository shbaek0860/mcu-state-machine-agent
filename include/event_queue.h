#ifndef EVENT_QUEUE_H
#define EVENT_QUEUE_H

#include <stdbool.h>
#include "heater_fsm.h"

#define EVENT_QUEUE_SIZE 16

void EventQueue_Init(void);
bool EventQueue_Push(HeaterEvent_t event);
bool EventQueue_Pop(HeaterEvent_t* out_event);
bool EventQueue_IsEmpty(void);

#endif // EVENT_QUEUE_H
