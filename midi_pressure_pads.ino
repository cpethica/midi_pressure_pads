/*********************************************************
This is a library for the MPR121 12-channel Capacitive touch sensor

Designed specifically to work with the MPR121 Breakout in the Adafruit shop 
  ----> https://www.adafruit.com/products/

These sensors use I2C communicate, at least 2 pins are required 
to interface

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada for Adafruit Industries.  
BSD license, all text above must be included in any redistribution
**********************************************************/

// Include the Bounce2 library found here :
// https://github.com/thomasfredericks/Bounce2
#include <Bounce2.h>
#include <MIDI.h>

#define ledPin 8    // indicator LED - ON/OFF AND MIDI
// number of buttons
int NumButtons = 4;
// button pins
int BUTTONS[] = {1, 2, 3, 4};
// button states
int value[] = {LOW, LOW, LOW, LOW};

MIDI_CREATE_DEFAULT_INSTANCE();

// Instantiate Bounce objects
Bounce debouncer1 = Bounce(); 
Bounce debouncer2 = Bounce(); 
Bounce debouncer3 = Bounce();
Bounce debouncer4 = Bounce();

void setup() {
   MIDI.begin(4); // Set MIDI channel, MIDI_CHANNEL_OMNI = all, number = channel 
   //Serial.begin(115200);

   pinMode(ledPin, OUTPUT);

// pull up all button pins
  for (int i = 0; i < NumButtons; i++) {
   pinMode(BUTTONS[i],INPUT_PULLUP);
  }
  
  debouncer1.attach(BUTTONS[0]);
  debouncer1.interval(5); // interval in ms

  debouncer2.attach(BUTTONS[1]);
  debouncer2.interval(5); // interval in ms

  debouncer3.attach(BUTTONS[2]);
  debouncer3.interval(5); // interval in ms

  debouncer4.attach(BUTTONS[3]);
  debouncer4.interval(5); // interval in ms
}

void loop() {
  
  // Update the Bounce instances :
  debouncer1.update();
  debouncer2.update();
  debouncer3.update();
  debouncer4.update();  
 
  // Get the updated values :
  value[0] == debouncer1.read();
  value[1] == debouncer2.read();
  value[2] == debouncer3.read();
  value[3] == debouncer4.read();

// send notes if button is pressed (check for LOW state and then send note 60 onwards)
  for (int i=0; i<NumButtons; i++) {
    if (value[i] = LOW) {
      MIDI.sendNoteOn(60+i, 127, 1);
      digitalWrite(ledPin, HIGH);
      //Serial.print(i); Serial.println("On");
    }
    // send note off
    if (value[i] = HIGH) {
      MIDI.sendNoteOff(60+i, 127, 1);
      digitalWrite(ledPin, LOW);
      //Serial.print(i); Serial.println("Off");
    }
  }
}
