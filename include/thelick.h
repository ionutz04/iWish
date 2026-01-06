        // Auto-generated from robsoncouto/arduino-songs
        // Song: thelick
        #include <Notes.h>
        #pragma once
        // tempo for this song
        int tempo = 108;

        // melody for this song
        int melody[] = {

  // The Lick 
  NOTE_D4,8, NOTE_E4,8, NOTE_F4,8, NOTE_G4,8, NOTE_E4,4, NOTE_C4,8, NOTE_D4,1,

};

        // number of notes
        int notes = sizeof(melody) / sizeof(melody[0]) / 2;

        // whole note duration in ms
        int wholenote = (60000 * 4) / tempo;

        // durations array - to be computed from melody at runtime
        int durations[sizeof(melody) / sizeof(melody[0]) / 2];
