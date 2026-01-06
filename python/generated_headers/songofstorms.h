        // Auto-generated from robsoncouto/arduino-songs
        // Song: songofstorms
        #include <Notes.h>
        #pragma once
        // tempo for this song
        int tempo = 108;

        // melody for this song
        int melody[] = {

  // Song of storms - The Legend of Zelda Ocarina of Time. 
  // Score available at https://musescore.com/user/4957541/scores/1545401

  NOTE_D4,4, NOTE_A4,4, NOTE_A4,4,
  REST,8, NOTE_E4,8, NOTE_B4,2,
  NOTE_F4,4, NOTE_C5,4, NOTE_C5,4,
  REST,8, NOTE_E4,8, NOTE_B4,2,
  NOTE_D4,4, NOTE_A4,4, NOTE_A4,4,
  REST,8, NOTE_E4,8, NOTE_B4,2,
  NOTE_F4,4, NOTE_C5,4, NOTE_C5,4,
  REST,8, NOTE_E4,8, NOTE_B4,2,
  NOTE_D4,8, NOTE_F4,8, NOTE_D5,2,

  NOTE_D4,8, NOTE_F4,8, NOTE_D5,2,
  NOTE_E5,-4, NOTE_F5,8, NOTE_E5,8, NOTE_E5,8,
  NOTE_E5,8, NOTE_C5,8, NOTE_A4,2,
  NOTE_A4,4, NOTE_D4,4, NOTE_F4,8, NOTE_G4,8,
  NOTE_A4,-2,
  NOTE_A4,4, NOTE_D4,4, NOTE_F4,8, NOTE_G4,8,
  NOTE_E4,-2,
  NOTE_D4,8, NOTE_F4,8, NOTE_D5,2,
  NOTE_D4,8, NOTE_F4,8, NOTE_D5,2,

  NOTE_E5,-4, NOTE_F5,8, NOTE_E5,8, NOTE_E5,8,
  NOTE_E5,8, NOTE_C5,8, NOTE_A4,2,
  NOTE_A4,4, NOTE_D4,4, NOTE_F4,8, NOTE_G4,8,
  NOTE_A4,2, NOTE_A4,4,
  NOTE_D4,1,
};

        // number of notes
        int notes = sizeof(melody) / sizeof(melody[0]) / 2;

        // whole note duration in ms
        int wholenote = (60000 * 4) / tempo;

        // durations array - to be computed from melody at runtime
        int durations[sizeof(melody) / sizeof(melody[0]) / 2];
