#ifndef _NOTE_H_
#define _NOTE_H_
#include <stdint.h>
#define C4 9579
#define D4 8513
#define E4 7575
#define F4 7163
#define G4 6377
#define A4 5782
#define B4 5062
#define C5 4778

typedef struct {
	uint32_t periodCycles;
	uint8_t duration12thnotes;
	uint8_t dynamicPercent;
}Note;
#endif