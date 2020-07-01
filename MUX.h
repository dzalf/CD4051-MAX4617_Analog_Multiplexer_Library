
// Library: MUX Abstraction for analog multiplexers including MAX4617 and CD4051 or similar
// Version: 1.1.9
// Developer: Daniel Melendrez
// email: dmelendrez(at)gmail(dot)com
// Category: Analog Devices
// Date: Dec 2018 - Initial release
//       Mar 2009 - Updated constructor to receive the enable pin
//       July 2020 - Minor corrections. semver updated

#ifndef MUX_h
#define MUX_h

#include "Arduino.h"

class MUX {

  public:
  
    //constructor
    MUX(uint8_t pinC, uint8_t pinB, uint8_t pinA, uint8_t pinEn);

    // Pin A is the LSB; PinEn is active Low. Drive pins high to set all switches off

    // Methods and variables
	
    uint8_t cp[3] = {0, 0, 0}; // MAX4617/CD4051 use 3 addressing pins for up to 8 sensors per MUX
    
    void setup(void);
    void selectChannel(uint8_t ch);
    void enable(void);
    void disable(void);

  private:

    uint8_t _pinA;
    uint8_t _pinB;
    uint8_t _pinC;
    uint8_t _pinEn;
    bool _enabled = false;

};

#endif
