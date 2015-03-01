#include "MusicDriver.h"
#include "Note.h"
Note* currentNote;
#define TRUE 1
#define FALSE 0
#define BASS_TAG_SIZE 9
Note bass_tag[BASS_TAG_SIZE] = {
{Aflat4, 12, 0},{Aflat4, 60, 100},{A4, 12, 0},{A4, 60, 100},
{Bflat4, 12, 0},{Bflat4, 60, 100},{B4, 12, 100},{B4,12,0},{B4,85,100}};
#define MEL_TAG_SIZE 36
Note tag_mel[MEL_TAG_SIZE] = {
{Aflat3, 8, 100},{Aflat3, 4, 0},{D5, 8, 100},{D5, 4, 0},
{E5, 12, 0},{D5, 8, 100},{D5, 4, 0},{D5, 8, 100},
{D5, 4, 0},{E5, 12, 0},{A3, 8, 100},{A3, 4, 0},
{Eflat5, 8, 100},{Eflat5, 4, 0},{E5, 12, 0},{Eflat5, 8, 100},
{Eflat5, 4, 0},{Eflat5, 8, 100},{Eflat5, 4, 0},{E5, 12, 0},
{Bflat3, 8, 100},{Bflat3, 4, 0},{E5, 8, 100},{E5, 4, 0},
{E5, 12, 0},{E5, 8, 100},{E5, 4, 0},{E5, 8, 100},
{E5, 4, 0},{E5, 12, 0},{F5, 8, 100},{F5, 4, 0},
{E5, 12, 0},{F5, 8, 100},{F5, 4, 0},{F5, 84, 100},};
#define SIZE 308
Note music[SIZE] = {
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

#define BASS_SIZE 384
Note bass[BASS_SIZE] = {
{D3, 8, 100},{D3, 4, 0},{D3, 8, 100},{D3, 4, 0},
{E5, 12, 0},{D3, 8, 100},{D3, 4, 0},{E5, 12, 0},
{D3, 8, 100},{D3, 4, 0},{D3, 8, 100},{D3, 4, 0},
{E5, 12, 0},{E5, 12, 0},{E5, 12, 0},{E5, 12, 0},
{E5, 12, 0},{G3, 8, 100},{G3, 4, 0},{E5, 12, 0},
{E5, 12, 0},{E5, 12, 0},{E5, 12, 0},{G3, 8, 100},
{G3, 4, 0},{E5, 12, 0},{E5, 12, 0},{E3, 8, 100},
{E3, 4, 0},{E5, 12, 0},{E5, 12, 0},{C2, 8, 100},
{C2, 4, 0},{E5, 12, 0},{E5, 12, 0},{F3, 8, 100},
{F3, 4, 0},{E5, 12, 0},{G3, 8, 100},{G3, 4, 0},
{E5, 12, 0},{Gflat3, 8, 100},{Gflat3, 4, 0},{F3, 8, 100},
{F3, 4, 0},{E5, 12, 0},{E3, 12, 100},{E3, 4, 0},
{C4, 12, 100},{C4, 4, 0},{E4, 12, 100},{E4, 4, 0},
{F4, 8, 100},{F4, 4, 0},{E5, 12, 0},{D4, 8, 100},
{D4, 4, 0},{E4, 8, 100},{E4, 4, 0},{E5, 12, 0},
{C4, 8, 100},{C4, 4, 0},{E5, 12, 0},{A3, 8, 100},
{A3, 4, 0},{B3, 8, 100},{B3, 4, 0},{G3, 8, 100},
{G3, 4, 0},{E5, 12, 0},{E5, 12, 0},{G3, 8, 100},
{G3, 4, 0},{E5, 12, 0},{E5, 12, 0},{E3, 8, 100},
{E3, 4, 0},{E5, 12, 0},{E5, 12, 0},{C2, 8, 100},
{C2, 4, 0},{E5, 12, 0},{E5, 12, 0},{F3, 8, 100},
{F3, 4, 0},{E5, 12, 0},{G3, 8, 100},{G3, 4, 0},
{E5, 12, 0},{Gflat3, 8, 100},{Gflat3, 4, 0},{F3, 8, 100},
{F3, 4, 0},{E5, 12, 0},{E3, 12, 100},{E3, 4, 0},
{C4, 12, 100},{C4, 4, 0},{E4, 12, 100},{E4, 4, 0},
{F4, 8, 100},{F4, 4, 0},{E5, 12, 0},{D4, 8, 100},
{D4, 4, 0},{E4, 8, 100},{E4, 4, 0},{E5, 12, 0},
{C4, 8, 100},{C4, 4, 0},{E5, 12, 0},{A3, 8, 100},
{A3, 4, 0},{B3, 8, 100},{B3, 4, 0},{G3, 8, 100},
{G3, 4, 0},{E5, 12, 0},{E5, 12, 0},{E5, 12, 0},
{E5, 12, 0},{E5, 8, 100},{E5, 4, 0},{Eflat5, 8, 100},
{Eflat5, 4, 0},{D5, 8, 100},{D5, 4, 0},{B4, 8, 100},
{B4, 4, 0},{E5, 12, 0},{C5, 8, 100},{C5, 4, 0},
{E5, 12, 0},{E4, 8, 100},{E4, 4, 0},{F4, 8, 100},
{F4, 4, 0},{G4, 8, 100},{G4, 4, 0},{E5, 12, 0},
{C4, 8, 100},{C4, 4, 0},{E4, 8, 100},{E4, 4, 0},
{F4, 8, 100},{F4, 4, 0},{E5, 12, 0},{E5, 12, 0},
{E5, 8, 100},{E5, 4, 0},{Eflat5, 8, 100},{Eflat5, 4, 0},
{D5, 8, 100},{D5, 4, 0},{B4, 8, 100},{B4, 4, 0},
{E5, 12, 0},{C5, 8, 100},{C5, 4, 0},{E5, 12, 0},
{F5, 8, 100},{F5, 4, 0},{E5, 12, 0},{F5, 8, 100},
{F5, 4, 0},{F5, 8, 100},{F5, 4, 0},{E5, 12, 0},
{E5, 12, 0},{E5, 12, 0},{E5, 12, 0},{E5, 12, 0},
{E5, 8, 100},{E5, 4, 0},{Eflat5, 8, 100},{Eflat5, 4, 0},
{D5, 8, 100},{D5, 4, 0},{B4, 8, 100},{B4, 4, 0},
{E5, 12, 0},{C5, 8, 100},{C5, 4, 0},{E5, 12, 0},
{E4, 8, 100},{E4, 4, 0},{F4, 8, 100},{F4, 4, 0},
{G4, 8, 100},{G4, 4, 0},{E5, 12, 0},{C4, 8, 100},
{C4, 4, 0},{E4, 8, 100},{E4, 4, 0},{F4, 8, 100},
{F4, 4, 0},{E5, 12, 0},{E5, 12, 0},{Aflat3, 8, 100},
{Aflat3, 4, 0},{E5, 12, 0},{E5, 12, 0},{Bflat3, 8, 100},
{Bflat3, 4, 0},{E5, 12, 0},{E5, 12, 0},{C4, 8, 100},
{C4, 4, 0},{E5, 12, 0},{E5, 12, 0},{E5, 12, 0},
{E5, 12, 0},{E5, 12, 0},{E5, 12, 0},{E5, 12, 0},
{E5, 12, 0},{E5, 12, 0},{E5, 8, 100},{E5, 4, 0},
{Eflat5, 8, 100},{Eflat5, 4, 0},{D5, 8, 100},{D5, 4, 0},
{B4, 8, 100},{B4, 4, 0},{E5, 12, 0},{C5, 8, 100},
{C5, 4, 0},{E5, 12, 0},{E4, 8, 100},{E4, 4, 0},
{F4, 8, 100},{F4, 4, 0},{G4, 8, 100},{G4, 4, 0},
{E5, 12, 0},{C4, 8, 100},{C4, 4, 0},{E4, 8, 100},
{E4, 4, 0},{F4, 8, 100},{F4, 4, 0},{E5, 12, 0},
{E5, 12, 0},{E5, 8, 100},{E5, 4, 0},{Eflat5, 8, 100},
{Eflat5, 4, 0},{D5, 8, 100},{D5, 4, 0},{B4, 8, 100},
{B4, 4, 0},{E5, 12, 0},{C5, 8, 100},{C5, 4, 0},
{E5, 12, 0},{F5, 8, 100},{F5, 4, 0},{E5, 12, 0},
{F5, 8, 100},{F5, 4, 0},{F5, 8, 100},{F5, 4, 0},
{E5, 12, 0},{E5, 12, 0},{E5, 12, 0},{E5, 12, 0},
{E5, 12, 0},{E5, 8, 100},{E5, 4, 0},{Eflat5, 8, 100},
{Eflat5, 4, 0},{D5, 8, 100},{D5, 4, 0},{B4, 8, 100},
{B4, 4, 0},{E5, 12, 0},{C5, 8, 100},{C5, 4, 0},
{E5, 12, 0},{E4, 8, 100},{E4, 4, 0},{F4, 8, 100},
{F4, 4, 0},{G4, 8, 100},{G4, 4, 0},{E5, 12, 0},
{C4, 8, 100},{C4, 4, 0},{E4, 8, 100},{E4, 4, 0},
{F4, 8, 100},{F4, 4, 0},{E5, 12, 0},{E5, 12, 0},
{Aflat3, 8, 100},{Aflat3, 4, 0},{E5, 12, 0},{E5, 12, 0},
{Bflat3, 8, 100},{Bflat3, 4, 0},{E5, 12, 0},{E5, 12, 0},
{C4, 8, 100},{C4, 4, 0},{E5, 12, 0},{E5, 12, 0},
{E5, 12, 0},{E5, 12, 0},{E5, 12, 0},{E5, 12, 0},
{E5, 12, 0},{Aflat2, 8, 100},{Aflat2, 4, 0},{Aflat4, 8, 100},
{Aflat4, 4, 0},{E5, 12, 0},{Eflat3, 8, 100},{Eflat3, 4, 0},
{E5, 12, 0},{Aflat4, 8, 100},{Aflat4, 4, 0},{Aflat3, 8, 100},
{Aflat3, 4, 0},{E5, 12, 0},{G3, 8, 100},{G3, 4, 0},
{E4, 8, 100},{E4, 4, 0},{E5, 12, 0},{C3, 8, 100},
{C3, 4, 0},{C4, 8, 100},{C4, 4, 0},{E5, 12, 0},
{E5, 12, 0},{E5, 12, 0},{Aflat2, 8, 100},{Aflat2, 4, 0},
{Aflat4, 8, 100},{Aflat4, 4, 0},{E5, 12, 0},{Eflat3, 8, 100},
{Eflat3, 4, 0},{E5, 12, 0},{Aflat4, 8, 100},{Aflat4, 4, 0},
{Aflat3, 8, 100},{Aflat3, 4, 0},{E5, 12, 0},{E5, 12, 0},
{E5, 12, 0},{E5, 12, 0},{E5, 12, 0},{E5, 12, 0},
{E5, 12, 0},{E5, 12, 0},{E5, 12, 0},{Aflat2, 8, 100},
{Aflat2, 4, 0},{Aflat4, 8, 100},{Aflat4, 4, 0},{E5, 12, 0},
{Eflat3, 8, 100},{Eflat3, 4, 0},{E5, 12, 0},{Aflat4, 8, 100},
{Aflat4, 4, 0},{Aflat3, 8, 100},{Aflat3, 4, 0},{E5, 12, 0},
{G3, 8, 100},{G3, 4, 0},{E4, 8, 100},{E4, 4, 0},
{E5, 12, 0},{C3, 8, 100},{C3, 4, 0},{C4, 8, 100},
{C4, 4, 0},{E5, 12, 0},{E5, 12, 0},{E5, 12, 0},};

Instrument synth = {
  2048,2448,2832,3186,3496,3751,3940,4057,4095,4057,3940,
  3751,3496,3186,2832,2448,2048,1648,1264,910,600,345,
  156,39,0,39,156,345,600,910,1264,1648};

uint32_t ind;
uint32_t bass_ind;
uint32_t tag_ind;
uint32_t tag_bass_ind;
uint32_t currentMelodyDuration = 0;
uint32_t currentBassDuration = 0;
uint32_t tagCurrentMelodyDuration = 0;
uint32_t tagCurrentBassDuration = 0;
uint8_t onTag = FALSE;
uint8_t doubleTime = FALSE;
void MusicDriver_Init(void){
	ind = 0;
	bass_ind = 0;
	tag_ind = 0;
	tag_bass_ind = 0;
}
void MusicDriver_reset(void){
	ind = 0;
	bass_ind = 0;
}
/*
void MusicDriver_getBass(Note** currentNote, Instrument** currentInstrument){
	static int currentDuration = 0;
	if (currentDuration > bass[ind].duration12thnotes){
		currentDuration = 0;
		ind = (ind + 1) % SIZE;
	} else {
		++currentDuration;
	}
	*currentNote = &bass[ind];
	*currentInstrument = &synth;
}
*/
void MusicDriver_setDoubleTime(uint8_t val){
	doubleTime = val;
	if (val == TRUE){
		MusicDriver_playTag();
	}
}

void MusicDriver_playTag(){
	onTag = TRUE;
	currentMelodyDuration = 0;
	currentBassDuration = 0;
}
void MusicDriver_getMelody(Note** currentNote, Instrument** currentInstrument){
	/*
	i/o parameters -
		currentNotes - pointer to a pointer to be populated with a list of the notes currently playing
	  currentInstruments - pointer to a pointer to be populated with a list of the instruments currently playing
	output:
		number of elements in the above arrays
	*/
	if (!onTag){
		int32_t comp_val = music[ind].duration12thnotes;
		if (doubleTime){
			comp_val /= 2;
		}
		if (currentMelodyDuration > comp_val){
			currentMelodyDuration = 0;
			ind = (ind + 1);
			if (ind == SIZE){
				doubleTime = FALSE;
				*currentNote = &music[0];
				*currentInstrument = &synth;
				ind = 0;
				return;
			}
		} else {
			++currentMelodyDuration;
		}
		*currentNote = &music[ind];
		*currentInstrument = &synth;
	} else {
		//if (currentDuration > music[ind].duration12thnotes){
		if (tagCurrentMelodyDuration > tag_mel[tag_ind].duration12thnotes){
			tagCurrentMelodyDuration = 0;
			tag_ind = (tag_ind + 1);
			if (tag_ind == MEL_TAG_SIZE){
				tag_ind = 0;
				onTag = FALSE;
				doubleTime = TRUE;
				MusicDriver_getMelody(currentNote, currentInstrument);
			}
		} else {
			++tagCurrentMelodyDuration;
		}
		//*currentNote = &music[ind];
		*currentNote = &tag_mel[tag_ind];
		*currentInstrument = &synth;
		
	}
}

void MusicDriver_getBass(Note** currentNote, Instrument** currentInstrument){
	/*
	i/o parameters -
		currentNotes - pointer to a pointer to be populated with a list of the notes currently playing
	  currentInstruments - pointer to a pointer to be populated with a list of the instruments currently playing
	output:
		number of elements in the above arrays
	*/
	if (!onTag){
		int32_t comp_val = bass[ind].duration12thnotes;
		if (doubleTime){
			comp_val /= 2;
		}
		if (currentBassDuration > comp_val){
			currentBassDuration = 0;
			bass_ind = (bass_ind + 1);
			if (bass_ind == BASS_SIZE){
				doubleTime = FALSE;
				*currentNote = &bass[0];
				*currentInstrument = &synth;
				bass_ind = 0;
				return;
			}
		} else {
			++currentBassDuration;
		}
		*currentNote = &bass[bass_ind];
		*currentInstrument = &synth;
	} else {
		if (tagCurrentBassDuration > bass_tag[tag_bass_ind].duration12thnotes){
			tagCurrentBassDuration = 0;
			tag_bass_ind = (tag_bass_ind + 1);
			if (tag_bass_ind == BASS_TAG_SIZE){
				tag_bass_ind = 0;
				onTag = FALSE;
				doubleTime = TRUE;
				MusicDriver_getBass(currentNote, currentInstrument);
			}
		} else {
			++tagCurrentBassDuration;
		}
		*currentNote = &bass_tag[tag_bass_ind];
		*currentInstrument = &synth;
		
	}
}