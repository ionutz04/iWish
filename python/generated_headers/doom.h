// Auto-generated from robsoncouto/arduino-songs
// Song: doom
#include <Notes.h>
#pragma once
// tempo for this song
int tempo = 225;

// melody for this song


// number of notes
int notes = sizeof(melody) / sizeof(melody[0]) / 2;

// whole note duration in ms
int wholenote = (60000 * 4) / tempo;

// durations array - to be computed from melody at runtime
int durations[sizeof(melody) / sizeof(melody[0]) / 2];
