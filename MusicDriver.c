#include "MusicDriver.h"
#include "Note.h"
Note* currentNote;
#define SIZE 308
Note music[308] = {
{E5, 8, 100},{E5, 4, 0},{E5, 8, 100},{E5, 4, 0},
{E5, 12, 0},{E5, 8, 100},{E5, 4, 0},{E5, 12, 0},
{C5, 8, 100},{C5, 4, 0},{E5, 8, 100},{E5, 4, 0},
{E5, 12, 0},{G5, 8, 100},{G5, 4, 0},{E5, 12, 0},
{E5, 12, 0},{E5, 12, 0},{G4, 8, 100},{G4, 4, 0},
{E5, 12, 0},{E5, 12, 0},{E5, 12, 0},{C5, 8, 100},
{C5, 4, 0},{E5, 12, 0},{E5, 12, 0},{G4, 8, 100},
{G4, 4, 0},{E5, 12, 0},{E5, 12, 0},{E4, 8, 100},
{E4, 4, 0},{E5, 12, 0},{E5, 12, 0},{A4, 8, 100},
{A4, 4, 0},{E5, 12, 0},{B4, 8, 100},{B4, 4, 0},
{E5, 12, 0},{Bflat4, 8, 100},{Bflat4, 4, 0},{A4, 8, 100},
{A4, 4, 0},{E5, 12, 0},{G4, 12, 100},{G4, 4, 0},
{E5, 12, 100},{E5, 4, 0},{G5, 12, 100},{G5, 4, 0},
{A5, 8, 100},{A5, 4, 0},{E5, 12, 0},{F5, 8, 100},
{F5, 4, 0},{G5, 8, 100},{G5, 4, 0},{E5, 12, 0},
{E5, 8, 100},{E5, 4, 0},{E5, 12, 0},{C5, 8, 100},
{C5, 4, 0},{D5, 8, 100},{D5, 4, 0},{B4, 8, 100},
{B4, 4, 0},{E5, 12, 0},{E5, 12, 0},{C5, 8, 100},
{C5, 4, 0},{E5, 12, 0},{E5, 12, 0},{G4, 8, 100},
{G4, 4, 0},{E5, 12, 0},{E5, 12, 0},{E4, 8, 100},
{E4, 4, 0},{E5, 12, 0},{E5, 12, 0},{A4, 8, 100},
{A4, 4, 0},{E5, 12, 0},{B4, 8, 100},{B4, 4, 0},
{E5, 12, 0},{Bflat4, 8, 100},{Bflat4, 4, 0},{A4, 8, 100},
{A4, 4, 0},{E5, 12, 0},{G4, 12, 100},{G4, 4, 0},
{E5, 12, 100},{E5, 4, 0},{G5, 12, 100},{G5, 4, 0},
{A5, 8, 100},{A5, 4, 0},{E5, 12, 0},{F5, 8, 100},
{F5, 4, 0},{G5, 8, 100},{G5, 4, 0},{E5, 12, 0},
{E5, 8, 100},{E5, 4, 0},{E5, 12, 0},{C5, 8, 100},
{C5, 4, 0},{D5, 8, 100},{D5, 4, 0},{B4, 8, 100},
{B4, 4, 0},{E5, 12, 0},{E5, 12, 0},{C3, 8, 100},
{C3, 4, 0},{E5, 12, 0},{G5, 8, 100},{G5, 4, 0},
{Gflat5, 8, 100},{Gflat5, 4, 0},{F5, 8, 100},{F5, 4, 0},
{Eflat5, 8, 100},{Eflat5, 4, 0},{C4, 8, 100},{C4, 4, 0},
{E5, 8, 100},{E5, 4, 0},{F3, 8, 100},{F3, 4, 0},
{Aflat4, 8, 100},{Aflat4, 4, 0},{A4, 8, 100},{A4, 4, 0},
{C5, 8, 100},{C5, 4, 0},{C4, 8, 100},{C4, 4, 0},
{A4, 8, 100},{A4, 4, 0},{C5, 8, 100},{C5, 4, 0},
{D5, 8, 100},{D5, 4, 0},{C3, 8, 100},{C3, 4, 0},
{E5, 12, 0},{G5, 8, 100},{G5, 4, 0},{Gflat5, 8, 100},
{Gflat5, 4, 0},{F5, 8, 100},{F5, 4, 0},{Eflat5, 8, 100},
{Eflat5, 4, 0},{G3, 8, 100},{G3, 4, 0},{E5, 8, 100},
{E5, 4, 0},{E5, 12, 0},{C6, 8, 100},{C6, 4, 0},
{E5, 12, 0},{C6, 8, 100},{C6, 4, 0},{C6, 8, 100},
{C6, 4, 0},{E5, 12, 0},{G3, 8, 100},{G3, 4, 0},
{E5, 12, 0},{C3, 8, 100},{C3, 4, 0},{E5, 12, 0},
{G5, 8, 100},{G5, 4, 0},{Gflat5, 8, 100},{Gflat5, 4, 0},
{F5, 8, 100},{F5, 4, 0},{Eflat5, 8, 100},{Eflat5, 4, 0},
{C4, 8, 100},{C4, 4, 0},{E5, 8, 100},{E5, 4, 0},
{F3, 8, 100},{F3, 4, 0},{Aflat4, 8, 100},{Aflat4, 4, 0},
{A4, 8, 100},{A4, 4, 0},{C5, 8, 100},{C5, 4, 0},
{C4, 8, 100},{C4, 4, 0},{A4, 8, 100},{A4, 4, 0},
{C5, 8, 100},{C5, 4, 0},{D5, 8, 100},{D5, 4, 0},
{C3, 8, 100},{C3, 4, 0},{E5, 12, 0},{Eflat5, 8, 100},
{Eflat5, 4, 0},{E5, 12, 0},{E5, 12, 0},{D5, 8, 100},
{D5, 4, 0},{E5, 12, 0},{E5, 12, 0},{C5, 8, 100},
{C5, 4, 0},{E5, 12, 0},{E5, 12, 0},{G3, 8, 100},
{G3, 4, 0},{G3, 8, 100},{G3, 4, 0},{E5, 12, 0},
{C3, 8, 100},{C3, 4, 0},{E5, 12, 0},{C5, 8, 100},
{C5, 4, 0},{C5, 8, 100},{C5, 4, 0},{E5, 12, 0},
{C5, 8, 100},{C5, 4, 0},{E5, 12, 0},{C5, 8, 100},
{C5, 4, 0},{D5, 8, 100},{D5, 4, 0},{E5, 12, 0},
{E5, 8, 100},{E5, 4, 0},{C5, 8, 100},{C5, 4, 0},
{E5, 12, 0},{A4, 8, 100},{A4, 4, 0},{G4, 8, 100},
{G4, 4, 0},{E5, 12, 0},{G3, 8, 100},{G3, 4, 0},
{E5, 12, 0},{C5, 8, 100},{C5, 4, 0},{C5, 8, 100},
{C5, 4, 0},{E5, 12, 0},{C5, 8, 100},{C5, 4, 0},
{E5, 12, 0},{C5, 8, 100},{C5, 4, 0},{D5, 8, 100},
{D5, 4, 0},{E5, 8, 100},{E5, 4, 0},{G3, 8, 100},
{G3, 4, 0},{E5, 12, 0},{E5, 12, 0},{C3, 8, 100},
{C3, 4, 0},{E5, 12, 0},{E5, 12, 0},{G2, 8, 100},
{G2, 4, 0},{E5, 12, 0},{C5, 8, 100},{C5, 4, 0},
{C5, 8, 100},{C5, 4, 0},{E5, 12, 0},{C5, 8, 100},
{C5, 4, 0},{E5, 12, 0},{C5, 8, 100},{C5, 4, 0},
{D5, 8, 100},{D5, 4, 0},{E5, 12, 0},{E5, 8, 100},
{E5, 4, 0},{C5, 8, 100},{C5, 4, 0},{E5, 12, 0},
{A4, 8, 100},{A4, 4, 0},{G4, 8, 100},{G4, 4, 0},
{E5, 12, 0},{G3, 8, 100},{G3, 4, 0},{E5, 12, 0},};

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