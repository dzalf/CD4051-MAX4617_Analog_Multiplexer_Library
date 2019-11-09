# CD4051-MAX4617_Analog_Multiplexer_Library

**Yet another Arduino Library for 8-channel Analog Multiplexers/Demutiplexers**

Hi there!

I've written this library to help those who are using analog bidirectional multiplexers (MAX4617/CD4051) with microcontrollers such as Arduino, Teensy, STM or equivalent.

It is a simple yet useful layer of abstraction to simplify the use of these analog MUXes. Both models are electronically equivalent!

Usage:

1. Declare the triad of pins from the uC connected to the MUX's select pins in the order --> C, B, A (9,10,11 according to the datasheets)
2. Instantiate as many MUX objects as physical devices you need using --> **MUX** muxDevice(pinC, pinB, pinA)
3. Initialize the library in the Setup function --> muxDevice.setup();
4. To select a channel pass an integer value corresponding to the channel to be selected --> muxDevice(4); // to connect the input/output (common pin 3) to the switch from channel 4 (pin 1)
   
   **Remember that the permitted channel values are only from 0 to 7**
   
**Important:** Review the two included examples to get a better idea of the utility of this library.

Cheers!

dzalf :sunglasses:

**#TODO**

~~Sooon I will implement the activation/deactivation of the MUX from the library (Pin EN from MUX). For now you can simply tie this pin to GND to enable it. **Never leave the enable pin floating**~~

Add more examples of the usability of the library :;):
