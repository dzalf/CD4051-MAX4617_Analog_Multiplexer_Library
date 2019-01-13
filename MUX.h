
// Library: MUX Abstraction for analog multiplexers including MAX4617 and CD4051 or similar
// Version: 0.1
// Developer: Daniel Melendrez
// email: dmelendrez(at)gmail(dot)com
// Category: Analog Devices
// Date: Dec 2018

#ifndef MUX_h
#define MUX_h

#include "Arduino.h"

class MUX {

  public:
  
    //constructor
    MUX(uint8_t pinC, uint8_t pinB, uint8_t pinA);

    // Methods and variables
	
    uint8_t cp[3] = {0, 0, 0}; // MAX4617/CD4051 use 3 addressing pins for up to 8 sensors per MUX
    
	void setup(void);
    void selectChannel(uint8_t ch);

  private:

    uint8_t _pinA;
    uint8_t _pinB;
    uint8_t _pinC;

};

#endif
