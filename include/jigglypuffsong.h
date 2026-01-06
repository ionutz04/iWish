        // Auto-generated from robsoncouto/arduino-songs
        // Song: jigglypuffsong
        #include <Notes.h>
        #pragma once
        // tempo for this song
        int tempo = 85;

        // melody for this song
        int melody[] = {

  // Jigglypuff's Song
  // Score available at https://musescore.com/user/28109683/scores/5044153

  NOTE_D5,-4, NOTE_A5,8, NOTE_FS5,8, NOTE_D5,8,
  NOTE_E5,-4, NOTE_FS5,8, NOTE_G5,4,
  NOTE_FS5,-4, NOTE_E5,8, NOTE_FS5,4,
  NOTE_D5,-2,
  NOTE_D5,-4, NOTE_A5,8, NOTE_FS5,8, NOTE_D5,8,
  NOTE_E5,-4, NOTE_FS5,8, NOTE_G5,4,
  NOTE_FS5,-1,
  NOTE_D5,-4, NOTE_A5,8, NOTE_FS5,8, NOTE_D5,8,
  NOTE_E5,-4, NOTE_FS5,8, NOTE_G5,4,

  NOTE_FS5,-4, NOTE_E5,8, NOTE_FS5,4,
  NOTE_D5,-2,
  NOTE_D5,-4, NOTE_A5,8, NOTE_FS5,8, NOTE_D5,8,
  NOTE_E5,-4, NOTE_FS5,8, NOTE_G5,4,
  NOTE_FS5,-1,

};

        // number of notes
        int notes = sizeof(melody) / sizeof(melody[0]) / 2;

        // whole note duration in ms
        int wholenote = (60000 * 4) / tempo;

        // durations array - to be computed from melody at runtime
        int durations[sizeof(melody) / sizeof(melody[0]) / 2];
