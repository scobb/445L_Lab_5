#ifndef _TEMPO_TIMER_
#define _TEMPO_TIMER_
void TempoTimer_Init();
void TempoTimer_setHeartbeatTask(void(*task)(void));
void TempoTimer_arm();
void TempoTimer_disarm();

#endif