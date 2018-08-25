#include <cs-11m.h>
#include "slidePlay.h"

/*
  @author Michael crumpler
  CS 11m
  mdcrumpler@gmail.com

  Project: Light Theremin

  I/O: Project utilizes a Piezo speaker and photoreceptor

  Photoreceptor detects darkness levels and uses the value
  (multiplied by 32 to allow greater range of notes)
  to output the frequency to the Piezo

  There is a slide mode for smooth transitions between notes
  Sticatto mode which detects 10 light levels and plays these
  as corresponding notes, and melody mode which takes 10 note values
  and plays them in a song-like manner

*/
#define SENSOR 0
const int speakerPIN = 3;



void setup() {
  Serial.begin(9600);
  analogReference(DEFAULT);
  float messaround = 0;
  float othervariable = 0;

  Serial.println("Example of pass by reference:");
  delay(500);
  Serial.println("We will pass a funciton which modifies the variable messaround.");
  delay(500);
  Serial.print("The value of messaround is: ");
  Serial.println(messaround);
  Serial.print("The value of othervariable is: ");
  Serial.println(othervariable);

  Serial.println("Now we will take the cosine of messaround and put it in othervariable");
  othervariable = takingCosine(messaround);
  Serial.print("New messaround: ");
  Serial.println(messaround);
  Serial.print("New othervariable: ");
  Serial.println(othervariable);



  Serial.println("Welcome to the Light Theremin!");
  Serial.println();
  Serial.println("What would you like to run?");
  Serial.println("1. Melody mode \n 2. Sticatto mode \n 3. Slide mode");


}


void loop() {
  int serialinput = 0;

  String input = "Please enter input";

  Serial.println(input);
  if (Serial.available()) {
    serialinput = Serial.parseInt();
    Serial.println(serialinput);
  }
  if (serialinput == 1) {
    Serial.println("Melody mode!");
  }
  else if (serialinput == 2) {
    Serial.println("Sticatto mode!");
  }
  else if (serialinput == 3) {
    Serial.println("Slide mode!");
  }
  else if (serialinput < 0 || serialinput > 3) {
    reDo(serialinput);
  }
  while (serialinput == 1) {
    noteRepeat();
  }
  while (serialinput == 2) {
    sticattoMode();
  }
  while (serialinput == 3) {
    slideMode();
  }
  delay(1000);


}

/*
  Prints the array from Melody mode.
*/

void arrayPrint(const int Array[]) {
  int size = 10;

  for (int i = 0; i < size; i++) {
    Serial.print(Array[i]);
    Serial.print(" ");
  }


}

/*
  Melody mode

  Takes readings on a delay, puts them to an array, and plays them in order

*/

void noteRepeat() {
  int reading = 0;
  int readingArray[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  String redString;

  for (int i = 0; i < 10; i++) {
    reading = analogRead(SENSOR);
    reading = reading * 32;
    reading = constrain(reading, 31, 65530);
    readingArray[i] = (reading);
    delay(500);
  }
  arrayPrint(readingArray);
  for ( int j = 0; j < 10; j++) {
    for (int i = 0; i < 10; i++) {
      int playNote = readingArray[i];

      tone(speakerPIN, playNote);
      delay(100);
      noTone(speakerPIN);
      delay(500);
    }
    noTone(speakerPIN);
  }



}



/*
  Sticatto mode:

  will intake analogread on pin zero
  plays notes read on a delay
*/
void sticattoMode() {
  int playNote = 0;
  playNote = analogRead(0);
  playNote = playNote * 32;
  tone(speakerPIN, playNote);
  delay(100);
  noTone(speakerPIN);
  delay(100);
}


/*
  Slide mode

  Smooth transition between frequencies read by analogRead

*/

void slideMode() {
  int playNote = 0;
  
  playNote = analogRead(0);
  playNote = playNote * 32;

  slidePlay slide(speakerPIN);
  Serial.println(playNote);
  slide.playFreq(playNote);
}


float takingCosine(float &messaround) {
  float held;

  held = cos(messaround);

  return held;
}


/*
  Reruns request for user input if they do not input something between 1 and 3.
*/

void reDo(int &serialinput) {
  Serial.println("Error! Invalid input. Try again.");
  if (Serial.available()) {
    serialinput = Serial.parseInt();
    Serial.println(serialinput);
  }
  if (serialinput == 1) {
    Serial.println("Melody mode!");
  }
  else if (serialinput == 2) {
    Serial.println("Sticatto mode!");
  }
  else if (serialinput == 3) {
    Serial.println("Slide mode!");
  }
  else if (serialinput < 0 || serialinput > 3) {
    reDo(serialinput);
  }
}


