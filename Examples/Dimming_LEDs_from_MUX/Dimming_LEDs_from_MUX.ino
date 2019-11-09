/* Example for the usage of the MUX library

   In this case the MUX is used to write values through a PWM
   capable Pin to the MUX input and distribute that signal to all 8 channels
   in order to light up 8 LEDs connected to the outputs.
 * ********  This is useful as port expansion! *********
   Daniel Melendrez
   
   
   December 2018
   Ver: 0.1
   
   *****
   November 2019
   Ver: 0.2
   
*/

#include <MUX.h>

const int freqOut = 10;  // Pin that sends the PWM signal
byte channels;        // Variable to point at the channels

MUX mux(7, 6, 5, 4); // Instantiate a MUX object. Use pins [7,6,5.. and 4] from the uController as [C, B, A, EN] on the MUX

void setup() {

  mux.setup();    // Initialize the object
  channels = 0;
  pinMode(freqOut, OUTPUT);

  mux.enable();

}

void loop() {

  // Sequential lights routine using only 1 pin

  analogWrite(freqOut, 255);


  for (int i  = 0; i <= 100 ; i++) {
    mux.selectChannel(floor(random(0,7)));
    delay(80);
  }
  

  analogWrite(freqOut, 0);

  // Silly routine for dimming all 8 LEDs

  while (channels < 8) {

    mux.selectChannel(channels);

    for (int brightness = 0; brightness < 255; brightness++) {

      analogWrite(freqOut, brightness);
      delay(5);
    }
    channels++;
  }


  for (int i  = 0; i <= 7 ; i++) {
    mux.selectChannel(i);
    analogWrite(freqOut, 0); // Turn them off before starting again
  }

  channels = 0;
  delay(1000);
}