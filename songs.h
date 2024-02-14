/*
  Adapted by Milton Matuda to work with M5-NEMO.
  You cand find a list of #define for other octaves at Robson's Github.
  IG: @35mmatuda | https://github.com/Mmatuda
*/
/* 
  Super Mario Bros - Overworld theme 
  More songs available at https://github.com/robsoncouto/arduino-songs                                            
                                              
                                              Robson Couto, 2019
*/
#define NOTE_G5  784
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define REST      0

// change this to make the song slower or faster
int tempo = 200;

// notes of the melody followed by the duration.
// a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
// !!negative numbers are used to represent dotted notes,
// so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
int melody[] = {

  // Super Mario Bros theme
  // Score available at https://musescore.com/user/2123/scores/2145
  // Theme by Koji Kondo
  
  NOTE_E6,8, NOTE_E6,8, REST,8, NOTE_E6,8, REST,8, NOTE_C6,8, NOTE_E6,8, //WRITE YOUR MELODY HERE
  NOTE_G6,4, REST,2, NOTE_G5,2,
};

// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
// there are two values per note (pitch and duration), so for each note there are four bytes
int notes = sizeof(melody) / sizeof(melody[0]) / 2;

// this calculates the duration of a whole note in ms
int wholenote = (60000 * 4) / tempo;

int divider = 0, noteDuration = 0;

void setupSongs() {
  // iterate over the notes of the melody.
  // Remember, the array is twice the number of notes (notes + durations)
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }
#if defined(STICK_C_PLUS)
    // playing 2 octave up (2^2) due to proximity of frequencies and high noise on low freqs
    SPEAKER.tone(melody[thisNote]*4, noteDuration*0.9);
    SPEAKER.tone(0, noteDuration*0.1);
    // Wait for the specief duration before playing the next note.
    delay(noteDuration);
    SPEAKER.mute();
#elif defined(CARDPUTER)
    // we only play the note for 90% of the duration, leaving 10% as a pause
    SPEAKER.tone(melody[thisNote], noteDuration * 0.9);
    // Wait for the specief duration before playing the next note.
    delay(noteDuration);
#elif defined(STICK_C_PLUS2)
    // playing 2 octave up (2^2) due to proximity of frequencies and high noise on low freqs
    SPEAKER.tone(melody[thisNote]*4, noteDuration*0.9);
    SPEAKER.tone(0, noteDuration*0.1);
    // Wait for the specief duration before playing the next note.
    delay(noteDuration);
    SPEAKER.stop();
#endif
    
  }
}
