#include "MusicDriver.h"

uint32_t ind;
void MusicDriver_Init(void){
	ind = 0;
}
void MusicDriver_reset(void){
	ind = 0;
}
uint8_t MusicDriver_getNextTimeStep(Note* currentNotes, Instrument* currentInstruments){
	/*
	i/o parameters -
		currentNotes - pointer to be populated with a list of the notes currently playing
	  currentInstruments - pointer to be populated with a list of the instruments currently playing
	output:
		number of elements in the above arrays
	*/
	
	// ++ind;
	// currentNotes = &Music[ind].Notes;
	// currentInstruments = &Music[ind].Instruments;
	// return &Music[ind].num;
	
	
	return 0;
}