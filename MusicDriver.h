#ifndef _MUSIC_DRIVER_
#define _MUSIC_DRIVER_
#include <stdint.h>
#include "Note.h"
#include "Instrument.h"
void MusicDriver_Init(void);
void MusicDriver_reset(void);
uint8_t MusicDriver_getNextTimeStep(Note* currentNotes, Instrument* currentInstruments);



#endif