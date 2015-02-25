#ifndef _BUTTON_MANAGER_H_
#define _BUTTON_MANAGER_H_
void ButtonManager_Init();
void resetToMainScreen();
#define PD6       (*((volatile uint32_t *)0x40007100))
#endif