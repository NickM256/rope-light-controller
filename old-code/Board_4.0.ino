/*
  GUINO DASHBOARD TEMPLATE FOR THE ARDUINO. 
  It should be used with the GUINO Dashboard app.
  More info can be found here: www.hobye.dk
  
  Original code by Bliptronics.com Ben Moyes 2009
 */
#include <TimerOne.h>
#include "LPD6803.h"

/* room map

92----105---117
|            |
|            |
75           15
|            |
|            |
57-----46----33

*/

//Shift Reginster define where your pins are
const int ShiftlatchPin = 9;
const int ShiftdataPin = 7;
const int ShiftclockPin = 8;

byte Buttons[] = {
  1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0}; 
const int AnalogPins[5] = {0,1,2,3,4};
int AnalogInput[5] = {
  0,0,0,0,0};


////////////////////////////////////////////////////////////////////////////////////////////////////

void setup(){
  Serial.begin(9600);
  
  pinMode(ShiftlatchPin, OUTPUT);
  pinMode(ShiftclockPin, OUTPUT); 
  pinMode(ShiftdataPin, INPUT);
  pinMode(6, INPUT);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void loop(){
  if(digitalRead(6)==true){
  shiftIn();
  
  for(int x=0; x <= 15; x++)
    Serial.print(Buttons[x]);
   Serial.println();
  }
  
  /*Serial.print(analogRead(AnalogPins[0]));
  Serial.print("  ");
  Serial.print(analogRead(AnalogPins[1]));
  Serial.print("  ");
  Serial.print(analogRead(AnalogPins[2]));
  Serial.print("  ");
  Serial.print(analogRead(AnalogPins[3]));
  Serial.print("  ");
  Serial.println(analogRead(AnalogPins[4]));
*/
}







void shiftIn() {
  // The shift register only collects data for 10ms so reserved for toggle switches
  //Pulse the latch pin:
  digitalWrite(ShiftlatchPin,1);   //set it to 1 to collect parallel data
  //set it to 1 to collect parallel data, wait
  delayMicroseconds(20);  // origanaly 20

  digitalWrite(ShiftlatchPin,0);  //set it to 0 to transmit data serially  


  //while the shift register is in serial mode
  //collect each shift register into a byte
  //the register attached to the chip comes in first 


  //we will be holding the clock pin high 8 times (0,..,7) at the
  //end of each time through the for loop

  //at the begining of each loop when we set the clock low, it will
  //be doing the necessary low to high drop to cause the shift
  //register's DataPin to change state based on the value
  //of the next bit in its serial information flow.
  //The register transmits the information about the pins from pin 7 to pin 0
  //so that is why our function counts down
  int temp = 0;
  for (int i=15; i>=0; i--)
  {
    digitalWrite(ShiftclockPin, 0);
    delayMicroseconds(2);  // origanaly 2
    Buttons[i] = digitalRead(ShiftdataPin);
    digitalWrite(ShiftclockPin, 1);
  }
}


