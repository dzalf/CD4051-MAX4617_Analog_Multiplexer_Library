
// Library: MUX Abstraction for analog multiplexers including MAX4617 and CD4051 or similar
// Version: 1.1.9
// Developer: Daniel Melendrez
// email: dmelendrez(at)gmail(dot)com
// Category: Analog Devices
// Date: Dec 2018 - Initial release
//       Mar 2009 - Updated constructor to receive the enable pin
//       July 2020 - Minor corrections. semver updated

#include "AnalogMUX.h"

// Constructor

AnalogMUX::AnalogMUX(uint8_t pinC, uint8_t pinB, uint8_t pinA, uint8_t pinEn) {
  _pinA = pinA; 
  _pinB = pinB; 
  _pinC = pinC;
  _pinEn = pinEn;
  
  cp[0] = _pinA;
  cp[1] = _pinB;
  cp[2] = _pinC;
}

// Methods

void AnalogMUX::setup(void) {
	
	// Initialization of addressing pins
  for (int i  = 0; i < 3; i++) {
    pinMode(cp[i], OUTPUT);
  }
  
	// By default Channel 0 is selected
  for (int posPin  = 0; posPin < 3; posPin++) {
    digitalWrite(cp[posPin], LOW);
  }
  
  pinMode(_pinEn, OUTPUT);
  delay(50);
  disable();    // The device is disabled by default

}

void AnalogMUX::enable(){

  digitalWrite(_pinEn, LOW);
  _enabled = true;
}

void AnalogMUX::disable(){

  digitalWrite(_pinEn, HIGH);
  _enabled = false;
	
}

// Select channel by bit shifting
void AnalogMUX::selectChannel(uint8_t ch) {

  if(_enabled){
    for (int state = 0; state < 3; state++) {
      digitalWrite(cp[state], ch & 1);
      ch >>= 1;
    }
  }
}
