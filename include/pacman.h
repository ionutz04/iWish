        // Auto-generated from robsoncouto/arduino-songs
        // Song: pacman
        #include <Notes.h>
        #pragma once
        // tempo for this song
        int tempo = 105;

        // melody for this song
        int melody[] = {

  // Pacman
  // Score available at https://musescore.com/user/85429/scores/107109
  NOTE_B4, 16, NOTE_B5, 16, NOTE_FS5, 16, NOTE_DS5, 16, //1
  NOTE_B5, 32, NOTE_FS5, -16, NOTE_DS5, 8, NOTE_C5, 16,
  NOTE_C6, 16, NOTE_G6, 16, NOTE_E6, 16, NOTE_C6, 32, NOTE_G6, -16, NOTE_E6, 8,

  NOTE_B4, 16,  NOTE_B5, 16,  NOTE_FS5, 16,   NOTE_DS5, 16,  NOTE_B5, 32,  //2
  NOTE_FS5, -16, NOTE_DS5, 8,  NOTE_DS5, 32, NOTE_E5, 32,  NOTE_F5, 32,
  NOTE_F5, 32,  NOTE_FS5, 32,  NOTE_G5, 32,  NOTE_G5, 32, NOTE_GS5, 32,  NOTE_A5, 16, NOTE_B5, 8
};

        // number of notes
        int notes = sizeof(melody) / sizeof(melody[0]) / 2;

        // whole note duration in ms
        int wholenote = (60000 * 4) / tempo;

        // durations array - to be computed from melody at runtime
        int durations[sizeof(melody) / sizeof(melody[0]) / 2];
