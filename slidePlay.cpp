/*
Code to play the slidePlay class

playFreq takes the input frequency from the light sensor and puts it out as a slide mechanism
for the speaker
*/

#include "Arduino.h"
#include "slidePlay.h"

slidePlay::slidePlay(int speakerPin) {
  _speakerPin = speakerPin;
}

void slidePlay::playFreq(int frequency) {
  _frequency = frequency;
  tone(_speakerPin, _frequency);
}
