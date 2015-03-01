#ifndef _MUSIC_DRIVER_
#define _MUSIC_DRIVER_
#include <stdint.h>
#include "Note.h"
#include "Instrument.h"
void MusicDriver_Init(void);
void MusicDriver_reset(void);
void MusicDriver_getMelody(Note** currentNotes, Instrument** currentInstruments);
void MusicDriver_getBass(Note** currentNotes, Instrument** currentInstruments);

#endif