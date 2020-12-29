//One oscillator capacitive touch
// using lots of code from Sebastian Tomczak https://little-scale.blogspot.com/2017/05/teensy-36-basics-touchread.html

// this loads libraries that are required by Teensy
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform1;      //xy=290,213
AudioSynthWaveform       waveform2;      //xy=291,266
AudioMixer4              mixer1;         //xy=487,237
AudioOutputAnalog        dac1;           //xy=632,237
AudioConnection          patchCord1(waveform1, 0, mixer1, 1);
AudioConnection          patchCord2(waveform2, 0, mixer1, 2);
AudioConnection          patchCord3(mixer1, dac1);
// GUItool: end automatically generated code

//set up variables
int touchRead_pin = 0; //variable to store the input pin
int touchRead_pin2 = 1; //variable to store the second input pin
int thresh = 2300; // variable to store the touch threshold
int play_flag = 0; // variable that flags if sound is being played or not 1 = playing; 0 = not playing
int current; // variable used to store the value from the touch input pin
int play_flag2 = 0; // variable that flags if sound from the second apple is being played or not 1 = playing; 0 = not playing
int current2; // variable used to store the value from the second touch input pin

void setup() {
// put your setup code here, to run once:

AudioMemory(50); // Dynamic memory is allocated to be used exclusively by the Audio library
waveform1.begin(0, 100, WAVEFORM_TRIANGLE); // this sets up the 
// parameters of the wave form (volume, frequency, waveform type)
// change the middle number to change the audio frequency (pitch)
waveform2.begin(0, 180, WAVEFORM_TRIANGLE); // this sets up the parameters of the second wave form

 Serial.begin(9600); // initialize serial communication with computer - sets up the serial 
// monitor
}


// This is the loop, the program runs through these items then goes back to the start of the loop and does it again.
// This happens very very fast.
void loop() {
current = touchRead(touchRead_pin); // setting the ‘current’ variable
current2 = touchRead(touchRead_pin2); // setting the 'current2' variable
// Now the value from the touchRead function is compared to the threshold value.
 if(current > thresh && play_flag == 0) {
    play_flag = 1;
    waveform1.amplitude(0.2); // turn the volume up to 0.2  - 1 is full volume.
  }
  if(current < thresh && play_flag == 1) {
    play_flag = 0;
    waveform1.amplitude(0);  // turn the volume to 0 - no sound
    
  }
  
//repeat for the second apple
  if(current2 > thresh && play_flag2 == 0) {
    play_flag2 = 1;
    waveform2.amplitude(0.2); // turn the volume up to 0.2  
  }

//repeat for the second apple
  if(current2 < thresh && play_flag2 == 1) {
    play_flag2 = 0;
    waveform2.amplitude(0);  // turn the volume to 0 - no sound
  }

Serial.println(current); // this sends the data from the input pin which is stored in the variable -  “current” - to the serial monitor
delay(100);
}
