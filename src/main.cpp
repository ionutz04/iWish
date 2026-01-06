#include <Arduino.h>
#include <avr/io.h>
#include <merrychristmas.h>


volatile bool isPlaying = false;
volatile unsigned long lastInterruptTime = 0;
volatile bool buttonPressed = false;


int numNotes = sizeof(melody) / sizeof(melody[0]) / 2;
int currentNote = 0;


void buttonISR() {
    unsigned long currentTime = millis();
    if (currentTime - lastInterruptTime > 300) {
        isPlaying = !isPlaying;
        lastInterruptTime = currentTime;
        buttonPressed = true;
        
        if (!isPlaying) {
            noTone(8); 
            currentNote = 0;
        }
    }
}


void initADC() {

    ADMUX = (1 << REFS0);

    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}


uint16_t readADC(uint8_t channel) {

    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);

    ADCSRA |= (1 << ADSC);

    while (ADCSRA & (1 << ADSC));
    return ADC;
}

long myMap(long x, long in_min, long in_max, long out_min, long out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void setup() {
    
    DDRB |= (1 << DDB0);

    DDRD &= ~(1 << DDD2);   // Input
    PORTD |= (1 << PORTD2); // Enable pull-up

    initADC();

    attachInterrupt(digitalPinToInterrupt(2), buttonISR, FALLING);
}

void loop() {

    if (buttonPressed) {
        buttonPressed = false;
    }
    

    uint16_t potValue = readADC(0);
    int tempo = myMap(potValue, 0, 1023, 80, 250);
    int wholenote = (60000L * 4) / tempo;
    

    static unsigned long lastDebugPrint = 0;
    if (!isPlaying && (millis() - lastDebugPrint > 2000)) {
        lastDebugPrint = millis();
    }
    
    if (isPlaying) {
        if (currentNote < numNotes * 2) {
            int note = melody[currentNote];
            int divider = melody[currentNote + 1];
            int noteDuration;

            if (divider > 0) {
                noteDuration = wholenote / divider;
            } else {
                noteDuration = (wholenote / (-divider)) * 3 / 2;
            }

            if (note != REST) {
                tone(8, note, noteDuration * 9 / 10); 
                delay(noteDuration);
            } else {
                delay(noteDuration);
            }

            currentNote += 2;

            if (currentNote >= numNotes * 2) {
                currentNote = 0;
            }
        }
    }
}