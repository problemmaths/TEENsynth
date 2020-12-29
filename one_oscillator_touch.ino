//One oscillator capacitive touch
// using lots of code from Sebastian Tomczak https://little-scale.blogspot.com/2017/05/teensy-36-basics-touchread.html

// this loads libraries that are required by Teensy
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform1;      //xy=387,283
AudioOutputAnalog        dac1;           //xy=549,283
AudioConnection          patchCord1(waveform1, dac1);
// GUItool: end automatically generated code

//set up variables
int touchRead_pin = 0; //variable to store the input pin
int thresh = 2300; // variable to store the touch threshold
int play_flag = 0; // variable that flags if sound is being played or not 1 = playing; 0 = not playing
int current; // variable used to store the value from the touch input pin

void setup() {
// put your setup code here, to run once:

AudioMemory(50); // Dynamic memory is allocated to be used exclusively by the Audio library
waveform1.begin(0, 100, WAVEFORM_TRIANGLE); // this sets up the 
// parameters of the wave form (volume, frequency, waveform type)
// change the middle number to change the audio frequency (pitch)
// initialize serial communication with computer - sets up the serial 
// monitor

 Serial.begin(9600);
}


// This is the loop, the program runs through these items then goes back to the start of the loop and does it again.
// This happens very very fast.
void loop() {
current = touchRead(touchRead_pin); // setting the ‘current’ variable
// Now the value from the touchRead function is compared to the threshold value.
 if(current > thresh && play_flag == 0) {
    play_flag = 1;
    waveform1.amplitude(0.2); // turn the volume up to 0.2  - 1 is full volume.
  }
  if(current < thresh && play_flag == 1) {
    play_flag = 0;
    waveform1.amplitude(0);  // turn the volume to 0 - no sound
  }
Serial.println(current); // this sends the data from the input pin which is stored in the variable -  “current” - to the serial monitor
delay(100);
}
