        // Auto-generated from robsoncouto/arduino-songs
        // Song: startrekintro
        #include <Notes.h>
        #pragma once
        // tempo for this song
        int tempo = 80;

        // melody for this song
        int melody[] = {

  // Star Trek Intro
  // Score available at https://musescore.com/user/10768291/scores/4594271

  NOTE_D4, -8, NOTE_G4, 16, NOTE_C5, -4, 
  NOTE_B4, 8, NOTE_G4, -16, NOTE_E4, -16, NOTE_A4, -16,
  NOTE_D5, 2,

};

        // number of notes
        int notes = sizeof(melody) / sizeof(melody[0]) / 2;

        // whole note duration in ms
        int wholenote = (60000 * 4) / tempo;

        // durations array - to be computed from melody at runtime
        int durations[sizeof(melody) / sizeof(melody[0]) / 2];
