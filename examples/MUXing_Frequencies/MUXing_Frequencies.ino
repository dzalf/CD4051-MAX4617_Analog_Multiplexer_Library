
/*    This example measures up to 8 incoming frequencies connected to the uController Board.
 *     The signal can come from up to 8 different oscillators, for example and therefore it was designed
 *     around speed over accuracy
 *     
 *     It is based on the library FREQCount from Paul Stoffregen 
 *     
 *     ---> https://github.com/PaulStoffregen/FreqCount
 *     
 *     And in the case of Teensy Board requires Pin 13 to read the incoming frequency, therefore you MUST
 *     connect Pin 3 from the Analog MUX (4617/4051) to Pin 13 on Teensy Boards and Pin 5 on Arduino 1.
 *     Read the Documentation from this Library!
 *     
 *     Additionally it requires the installation of the Running Average Library from Rob Tillaart
 *     
 *     ---> https://github.com/RobTillaart/Arduino/tree/master/libraries/RunningAverage
 *     
 *     to obtain a smoother response
 *    
 *     Author: Daniel Melendrez
 *     
 *     Dec 2018 --> Ver: 0.2    
 *     Nov 2019 --> Ver: 0.3
 * 
 */

#include <FreqCount.h>
#include "RunningAverage.h"
#include "AnalogMUX.h"

const int deltaTime = 2;      // Time variable for waiting (in ms)
int samples = 0;
const int sensor;
const int acumulations = 10;    // Play with this value if you need faster response
const int maxSens = 5;         // This variable defines the limit of channels to read
long nowTime;
long previousTime, loopTime;
long elapsed;

AnalogMUX mux(14, 15, 16, 17);          // Instantiate an AnalogMUX object (C, B, A, Enable)

RunningAverage myRA(acumulations);  // Start a new Running average that will smooth out the output. Read the documentation for this library

void setup() {

  mux.setup();
  sensor = 0;
  myRA.clear(); 
  
  Serial.begin(2000000);  // Teensy 3.6 can run the serial port at this Baudrate. Check your board specifications
  
  previousTime = 0;
  loopTime = previousTime;
  
  FreqCount.begin(1);     // The gating for the FreqCount Library is the lowest possible (1 ms) aiming to achieve speed over precision
  mux.enable();
  
}

void loop() {

  mux.selectChannel(sensor);
  delay(1);

  Serial.print(sensor + 1);
  Serial.print(": ");

  while (samples < acumulations ) {

    nowTime = millis();

    if (nowTime - previousTime > deltaTime) {
      
      previousTime = nowTime;
      
      if (FreqCount.available()) {
        
        myRA.addValue(FreqCount.read() * 1000);
        
      }
      samples++;
    } 
  }

  Serial.print(myRA.getFastAverage());
  
  samples = 0;
  myRA.clear();

  if (sensor != maxSens) {    // This is only for formatting (visualization purposes)
    Serial.print(" ");
  }
  
  if (sensor == maxSens - 1) {
    
    elapsed = millis() - loopTime;
    
    Serial.print("t: ");
    Serial.print(elapsed);
    Serial.println(" ");          // Notice that this is the last print with carry return. See note below! **
    digitalWrite(ledPin, HIGH);
    
    loopTime = millis();
  }
  
  sensor++;
  
  if (sensor >= maxSens) sensor = 0;

}


/* NOTE
 *  
 *  Ths visualization should be something like: (for 6 channels)
 *  
 *  1: XX.XX 2: XX.XX 3: XX.XX 4: XX.XX 5: XX.XX 6: XX.XX t: 50
 *  1: XX.XX 2: XX.XX 3: XX.XX 4: XX.XX 5: XX.XX 6: XX.XX t: 50
 *  1: XX.XX 2: XX.XX 3: XX.XX 4: XX.XX 5: XX.XX 6: XX.XX t: 50
 *  1: XX.XX 2: XX.XX 3: XX.XX 4: XX.XX 5: XX.XX 6: XX.XX t: 50
 *  .
 *  .
 *  .
 *  .
 *  
 *  you get the idea ;)
 * 
 * */
 */
