/*
slidePlay.h

Library/class for the play modes on the theremin

Slide mode

*/

#ifndef slidePlay_h
#define slidePlay_h

#include "Arduino.h"

class slidePlay{
  public:
    slidePlay(int speakerPin);
    void playFreq(int frequency);
    
    private:
      int _frequency;
      int _speakerPin;
  };

  #endif

