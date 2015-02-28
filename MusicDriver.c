#include "MusicDriver.h"
#include "Note.h"
Note* currentNote;
#define SIZE 9
Note music[SIZE] = {{C4, 12, 100},
								{D4, 12, 100},
								{E4, 12, 100},
								{F4, 12, 100},
								{G4, 12, 100},
								{A4, 12, 100},
								{B4, 12, 100},
								{C5, 12, 100},
								{C5, 12, 0}};
Instrument synth = {
  2048,2448,2832,3186,3496,3751,3940,4057,4095,4057,3940,
  3751,3496,3186,2832,2448,2048,1648,1264,910,600,345,
  156,39,0,39,156,345,600,910,1264,1648};

uint32_t ind;
void MusicDriver_Init(void){
	ind = 0;
}
void MusicDriver_reset(void){
	ind = 0;
}
uint8_t MusicDriver_getNextTimeStep(Note** currentNote, Instrument** currentInstrument){
	/*
	i/o parameters -
		currentNotes - pointer to be populated with a list of the notes currently playing
	  currentInstruments - pointer to be populated with a list of the instruments currently playing
	output:
		number of elements in the above arrays
	*/
	static int currentDuration = 0;
	if (currentDuration > music[ind].duration12thnotes){
		currentDuration = 0;
		ind = (ind + 1) % SIZE;
	} else {
		++currentDuration;
	}
	*currentNote = &music[ind];
	*currentInstrument = &synth;
	return 1;
}