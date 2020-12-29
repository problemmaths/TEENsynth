
//
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
int touchRead_pin = A9; //variable to store the input pin number
int thresh = 2300; // variable to store the touch threshold for the fruit touch
int play_flag = 0; // variable that flags if sound is being played or not 1 = playing; 0 = not playing
int current; // variable used to store the value from the touch input pin
int pitchPin = A0; // variable storing which pin the pitch potentiometer will connect to
float pitchData; // variable used to store the data coming from the pitch potentiometer
float scaledPitch; //variable used to store the scaled data from the pitch potentiometer
int touchRead_pin2 = A9; //variable to store the input pin number
int thresh2 = 2300; // variable to store the touch threshold for the fruit touch
int play_flag2 = 0; // variable that flags if sound is being played or not 1 = playing; 0 = not playing
int current2; // variable used to store the value from the touch input pin
int pitchPin2 = A0; // variable storing which pin the pitch potentiometer will connect to
float pitchData2; // variable used to store the data coming from the pitch potentiometer
float scaledPitch2; //variable used to store the scaled data from the pitch potentiometer

void setup() {
// put your setup code here, to run once:

AudioMemory(50); // Dynamic memory is allocated to be used exclusively by the Audio library
waveform1.begin(0, 100, WAVEFORM_TRIANGLE); // this sets up the parameters of the wave form (volume, frequency, waveform type)
// change the middle number to change the audio frequency (pitch)

 // initialize serial communication with computer - sets up the serial monitor
  Serial.begin(9600);
}


// This is the loop, the program runs through these items then goes back to the start of the loop and does it again.
// This happens very very fast.

void loop() {
 
pitchData = analogRead(pitchPin);// Read the data coming from the pitch potentiometer and save it in the variable pitchData
scaledPitch = map(pitchData, 0, 1023, 20, 800); // Scale the value from the 'pitchData' variable and store it in the 'scaledPitch' variable
current = touchRead(touchRead_pin); // Read the value of 'touchRead_pin' and store it in the 'current' variable
pitchData2 = analogRead(pitchPin2);// Read the data coming from the pitch potentiometer and save it in the variable 'pitchData2'
scaledPitch2 = map(pitchData2, 0, 1023, 20, 800); // Scale the value from the 'pitchData' variable and store it in the 'scaledPitch2' variable
current2 = touchRead(touchRead_pin2); // Read the value of 'touchRead_pin' and store it in the 'current2' variable

waveform1.frequency(scaledPitch); // Set the frequency of waveform1 to the value of the 'scaledPitch' variable.
waveform2.frequency(scaledPitch2); // Set the frequency of waveform1 to the value of the 'scaledPitch2' variable.

// Now the value from the touchRead function is compared to the threshold value.

// If the touch value is above the threshold and the note is currently not playing,
// then a note on event is generated and the play flag is set to 1 indicating
// that there is now currently a note playing.
//If the touch value is above the threshold and the note is currently playing, no action is taken.

  if(current > thresh && play_flag == 0) {
    play_flag = 1;
    waveform1.amplitude(0.2); // turn the volume up to 0.2  - 1 is full volume.
  }

//If the touch value is below the threshold and the note is currently playing,
// then a note off event is generated and the play flag is set to 0 indicating
// that there is not currently a note playing.
//If the touch value is below the threshold and the note is currently not playing, no action is taken.

  if(current < thresh && play_flag == 1) {
    play_flag = 0;
    waveform1.amplitude(0);  // turn the volume to 0 - no sound
  }

  // Repeat the touchRead function for the second oscillator
  // If the touch value is above the threshold and the note is currently not playing,
// then a note on event is generated and the play flag is set to 1 indicating
// that there is now currently a note playing.
//If the touch value is above the threshold and the note is currently playing, no action is taken.

  if(current2 > thresh2 && play_flag2 == 0) {
    play_flag2 = 1;
    waveform1.amplitude(0.2); // turn the volume up to 0.2  - 1 is full volume.
  }

//If the touch value is below the threshold and the note is currently playing,
// then a note off event is generated and the play flag is set to 0 indicating
// that there is not currently a note playing.
//If the touch value is below the threshold and the note is currently not playing, no action is taken.

  if(current2 < thresh2 && play_flag2 == 1) {
    play_flag2 = 0;
    waveform2.amplitude(0);  // turn the volume to 0 - no sound
  }


    Serial.println(current); // this sends the data from the input pin which is stored in the variable -  current - to the serial monitor
  delay(100);
}
