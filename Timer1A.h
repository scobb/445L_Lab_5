#ifdef _TEMPO_TIMER_H_
#define _TEMPO_TIMER_H_

void TempoTimer_Init(uint32_t period);
void TempoTimer_setHeartbeatTask(void(*task)(void));
#endif