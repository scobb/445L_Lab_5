#ifndef _NOTE_H_
#define _NOTE_H_
#include <stdint.h>

typedef struct {
	uint32_t periodCycles;
	uint8_t duration12thnotes;
	uint8_t dynamicPercent;
}Note;
#endif