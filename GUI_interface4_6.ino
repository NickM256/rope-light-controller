/*
  GUINO DASHBOARD TEMPLATE FOR THE ARDUINO. 
  It should be used with the GUINO Dashboard app.
  More info can be found here: www.hobye.dk
  
  Original code by Bliptronics.com Ben Moyes 2009
 */
#include <TimerOne.h>   // Needed for ((LED strip))
#include "LPD6803.h"    // To talk to the LED strip
#include <HSBColor.h>   // For changing HSB to RGB

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
const int ShiftAll = 6;        //is on when a button is pushed

const int dataPin = 5;       // 'green' wire  || brown
const int clockPin = 4;      // 'ornge' wire  || brown W

byte Buttons[] = {
  1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0}; 
const int AnalogPins[5] = {0,1,2,3,4};
int AnalogInput[5] = {0,0,0,0,0};  //0=slider  1=slider  2=slider 3=nob 4=nob

// Set the first variable to the NUMBER of pixels. 20 = 20 pixels in a row
LPD6803 strip = LPD6803(120, dataPin, clockPin);


//         [y][x]
int Colors[5][3] = {    // stores the programs programible colors ((and inbeded colors))
//  r , g , b ?bit value?
  {255,0,0},
  {0,255,0},
  {0,0,255},
  {255,0,255},
  {255,255,0} //temparary color value
};

int Setting = 1;
int Last_Button_Pushed = 0;
boolean First = 1;

const double Color_Speed[4] = {1,1.11,1.2,.89}; //common denominator = 12
int Cycle_Location = 1; // goes from 1 to strip.numPixels()

int Speed;
int Langth;


////////////////////////////////////////////////////////////////////////////////////////////////////


void setup(){
                                                      Serial.begin(9600);
  pinMode(ShiftlatchPin, OUTPUT);
  pinMode(ShiftclockPin, OUTPUT); 
  pinMode(ShiftdataPin, INPUT);
  pinMode(ShiftAll, INPUT);
  
  
    // Light strip
  strip.setCPUmax(95); // start with 50% CPU usage. up this if the strand flickers or is slow
    // Start up the LED counter
  strip.begin();
    // Update the strip, to start they are all 'off'
  strip.show();
  
  
  Speed = 5;
  Langth = 5;
}


////////////////////////////////////////////////////////////////////////////////////////////////////


void loop(){
  //check_Buttons();
  //SolidColor(15,15,15,50);
                                                Serial.println("loop");
                                                Serial.println(Setting);
  RunSetting();
}


void RunSetting(){
  //Serial.println("RunSetting");
  
  if(Setting == 0){
    First = 1;
    
    int ColorTest[3];
    
    H2R_HSBtoRGB(int(AnalogInput[0]*0.25317), int(AnalogInput[1]*0.2493), int(AnalogInput[2]*0.2492), ColorTest);
    
                                              Serial.print("              ");
                                              Serial.println(ColorTest[0]);
                                              Serial.print("              ");
                                              Serial.println(ColorTest[1]);
                                              Serial.print("              ");
                                              Serial.println(ColorTest[2]);
    
    SolidColor(int((255-ColorTest[0])*0.12), int((255-ColorTest[1])*0.12), int((255-ColorTest[2])*0.12), 50);
  }
  else if(Setting == 1){
    First = 1;
    SolidColor(255,240,240,50);
  }
  else if(Setting == 2){
    First = 1;
    SolidColor(255,0,240,50);
  }
  else if(Setting == 3){
    First = 1;
    SolidColor(240,240,240,50);
  }
  else if(Setting == 4){
    First = 1;
    rainbowCycle(50);
  }
  else if(Setting == 5){
    First = 1;
    rainbowCycle2(50);
  }
  else if(Setting == 6){
    First = 1;
    rainbowCycle3(50);
  }
  else if(Setting == 7){
    First = 1;
    rainbowCycle4(50);
  }
  else if(Setting == 8){
    First = 1;
    rainbowCycle5(50);
  }
  else if(Setting == 9){
    First = 1;
    knight_rider(50);
  }
  else if(Setting == 10){
    First = 1;
    rainbowCycle6(50);
  }
  else if(Setting == 11){
    First = 1;
    Colors[0][0] = int(AnalogInput[0]/33);
    Colors[0][1] = int(AnalogInput[1]/33);
    Colors[0][2] = int(AnalogInput[2]/33);

    SolidColor(Colors[0][0], Colors[0][1], Colors[0][2], 50);
  }
  else if(Setting == 12){
    First = 1;
    
  }
  else if(Setting == 13){
    First = 1;
    
  }
  else if(Setting == 14){
    First = 1;
    
  }
  else if(Setting == 15){
    First = 1;
    
  }
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//        Light display funtions


int SolidColor(int r,int g,int b,uint8_t wait){
  First = 0;
  Serial.println("SolidColor");
  for(int p=0; p < strip.numPixels(); p++){
    strip.setPixelColor(p, b, g, r); // 0 to 31
  }
  strip.show();   // write all the pixels out
  delay(wait);
  
  
  do{
    check_Buttons();
  }while(First == 0);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////


void rainbowCycle(uint8_t wait) {
  int i=0, j=0;
  
  do{
      for (i=0; i < strip.numPixels(); i++) {
        // tricky math! we use each pixel as a fraction of the full 96-color wheel
        // (thats the i / strip.numPixels() part)
        // Then add in j which makes the colors go around per pixel
        // the % 96 is to make the wheel cycle around
        strip.setPixelColor(i, Wheel( ((i * 96 / strip.numPixels()) + j) % 96) );
      }
      strip.show();   // write all the pixels out
      delay(wait);
      
      if(j <! 96) // cycles of all 96 colors in the wheel
        j = 0;
      j++;
      
      check_Buttons();
  } while(Setting == 4);
  
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////


void rainbowCycle2(uint8_t wait) {
  int i=0, j=0;
  
  do{
    for (i=0; i < strip.numPixels()/2; i++) {
      // tricky math! we use each pixel as a fraction of the full 96-color wheel
      // (thats the i / strip.numPixels() part)
      // Then add in j which makes the colors go around per pixel
      // the % 96 is to make the wheel cycle around
      strip.setPixelColor((105+i)%strip.numPixels(), Wheel( ((i * 96 / strip.numPixels()) - j) % 96) );
      strip.setPixelColor((104-i)%strip.numPixels(), Wheel( ((i * 96 / strip.numPixels()) - j) % 96) );
    }
    strip.show();   // write all the pixels out
    delay(wait);
    
    if(j <! 96) // cycles of all 96 colors in the wheel
        j = 0;
      j++;
      
      check_Buttons();
  } while(Setting == 5);

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////


void rainbowCycle3(uint8_t wait) {
  int i=0, j=0;
  
  do{
    for (i=0; i < 19; i++) {    // langth
      // tricky math! we use each pixel as a fraction of the full 96-color wheel
      // (thats the i / strip.numPixels() part)
      // Then add in j which makes the colors go around per pixel
      // the % 96 is to make the wheel cycle around
      strip.setPixelColor((117+i)%strip.numPixels(), Wheel( ((i * 96 / strip.numPixels()) + j) % 96) );
      
      strip.setPixelColor((33-i)%strip.numPixels(), Wheel( ((i * 96 / strip.numPixels()) + j) % 96) );
      
      strip.setPixelColor((57+i)%strip.numPixels(), Wheel( ((i * 96 / strip.numPixels()) + j) % 96) );
      
      strip.setPixelColor((92-i)%strip.numPixels(), Wheel( ((i * 96 / strip.numPixels()) + j) % 96) );
    }
    for (i=0; i < 13; i++) {      //width
      // tricky math! we use each pixel as a fraction of the full 96-color wheel
      // (thats the i / strip.numPixels() part)
      // Then add in j which makes the colors go around per pixel
      // the % 96 is to make the wheel cycle around
      
      strip.setPixelColor((116-i)%strip.numPixels(), Wheel( ((i * 96 / strip.numPixels()) + j) % 96) );
      
      strip.setPixelColor((33+i)%strip.numPixels(), Wheel( ((i * 96 / strip.numPixels()) + j) % 96) );
      
      strip.setPixelColor((57-i)%strip.numPixels(), Wheel( ((i * 96 / strip.numPixels()) + j) % 96) );
      
      strip.setPixelColor((92+i)%strip.numPixels(), Wheel( ((i * 96 / strip.numPixels()) + j) % 96) );
      
    }
    strip.show();   // write all the pixels out
    delay(wait);
    
    
    if(j <! 96) // cycles of all 96 colors in the wheel
        j = 0;
    j++;
      
    check_Buttons();
  } while(Setting == 6);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////


void rainbowCycle4(uint8_t wait) {
  int i=0, j=0;
  
  do{
    for (i=0; i < 19; i++) {    // langth
      // tricky math! we use each pixel as a fraction of the full 96-color wheel
      // (thats the i / strip.numPixels() part)
      // Then add in j which makes the colors go around per pixel
      // the % 96 is to make the wheel cycle around
      strip.setPixelColor((117+i)%strip.numPixels(), Wheel( ((i * 96 / strip.numPixels()) - j) % 96) );
      
      strip.setPixelColor((33-i)%strip.numPixels(), Wheel( ((i * 96 / strip.numPixels()) - j) % 96) );
      
      strip.setPixelColor((57+i)%strip.numPixels(), Wheel( ((i * 96 / strip.numPixels()) - j) % 96) );
      
      strip.setPixelColor((92-i)%strip.numPixels(), Wheel( ((i * 96 / strip.numPixels()) - j) % 96) );
    }
    for (i=0; i < 13; i++) {      //width
      // tricky math! we use each pixel as a fraction of the full 96-color wheel
      // (thats the i / strip.numPixels() part)
      // Then add in j which makes the colors go around per pixel
      // the % 96 is to make the wheel cycle around
      
      strip.setPixelColor((116-i)%strip.numPixels(), Wheel( ((i * 96 / strip.numPixels()) - j) % 96) );
      
      strip.setPixelColor((33+i)%strip.numPixels(), Wheel( ((i * 96 / strip.numPixels()) - j) % 96) );
      
      strip.setPixelColor((57-i)%strip.numPixels(), Wheel( ((i * 96 / strip.numPixels()) - j) % 96) );
      
      strip.setPixelColor((92+i)%strip.numPixels(), Wheel( ((i * 96 / strip.numPixels()) - j) % 96) );
      
    }
    strip.show();   // write all the pixels out
    delay(wait);
    
    
    if(j <! 96) // cycles of all 96 colors in the wheel
        j = 0;
      j++;
      
      check_Buttons();
  } while(Setting == 7);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////


void rainbowCycle5(uint8_t wait) {
  
  int i=0, j=0;
  int y=1; //Intencity
  
  do{
    for (i=0; i < strip.numPixels(); i++) {
      // tricky math! we use each pixel as a fraction of the full 96-color wheel
      // (thats the i / strip.numPixels() part)
      // Then add in j which makes the colors go around per pixel
      // the % 96 is to make the wheel cycle around
      if(i == j%strip.numPixels())
        strip.setPixelColor(i, Wheel2( ((i * 96 / strip.numPixels()) + j) % 96, 1) );
      else if(i == (j+1)%strip.numPixels())
        strip.setPixelColor(i, Wheel2( ((i * 96 / strip.numPixels()) + j) % 96, 2) );
      else if(i == (j+2)%strip.numPixels())
        strip.setPixelColor(i, Wheel2( ((i * 96 / strip.numPixels()) + j) % 96, 3) );
      else if(i == (j+3)%strip.numPixels())
        strip.setPixelColor(i, Wheel2( ((i * 96 / strip.numPixels()) + j) % 96, 4) );
      else if(i == (j+4)%strip.numPixels())
        strip.setPixelColor(i, Wheel2( ((i * 96 / strip.numPixels()) + j) % 96, 5) );
      else if(i == (j+5)%strip.numPixels())
        strip.setPixelColor(i, Wheel2( ((i * 96 / strip.numPixels()) + j) % 96, 4) );
      else if(i == (j+6)%strip.numPixels())
        strip.setPixelColor(i, Wheel2( ((i * 96 / strip.numPixels()) + j) % 96, 3) );
      else if(i == (j+7)%strip.numPixels())
        strip.setPixelColor(i, Wheel2( ((i * 96 / strip.numPixels()) + j) % 96, 2) );
      else if(i == (j+8)%strip.numPixels())
        strip.setPixelColor(i, Wheel2( ((i * 96 / strip.numPixels()) + j) % 96, 1) );
      else
        strip.setPixelColor(i, Wheel( ((i * 96 / strip.numPixels()) + j) % 96) );
    }
    
     /*   strip.setPixelColor(j%strip.numPixels(), 0);
        strip.setPixelColor((j+1)%strip.numPixels(), 255, 255, 255);
        strip.setPixelColor((j+2)%strip.numPixels(), 255, 255, 255);
        strip.setPixelColor((j+3)%strip.numPixels(), 255, 255, 255);
        strip.setPixelColor((j+4)%strip.numPixels(), 255, 255, 255);
        strip.setPixelColor((j+5)%strip.numPixels(), 255, 255, 255);
        strip.setPixelColor((j+6)%strip.numPixels(), 255, 255, 255);  */
    
    strip.show();   // write all the pixels out
    delay(wait);
    
    if(j <! 96) // cycles of all 96 colors in the wheel
        j = 0;
      j++;
      
      check_Buttons();
  } while(Setting == 8);
  
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////


void rainbowCycle6(uint8_t wait) {
  int i=0, j=0;
  
  do{
      AnalogInput[3] = analogRead(AnalogPins[3]);
      AnalogInput[4] = analogRead(AnalogPins[4]);
      
      for (i=0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, Wheel( j % 96 ));
      }
      strip.show();   // write all the pixels out
      delay(wait);
      
      if(AnalogInput[3] < 512)
        delay(512-AnalogInput[3]);
      else
        j=j+int((AnalogInput[3]-512)/64);
      
      if(j <! 96) // cycles of all 96 colors in the wheel
        j = 0;
      j++;
      
      check_Buttons();
  } while(Setting == 10);
  
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////


void knight_rider(uint8_t wait) {
  int i = 0;
  
  do{
    //         offset
    int pixel1 = 0 + int(i*Color_Speed[0]); // the location of the pixel along the strip (0 to strip.numPixels()-1)
    int pixel2 = 25 + int(i*Color_Speed[1]);
    int pixel3 = 50 - int(i*Color_Speed[2]);
    int pixel4 = 100 - int(i*Color_Speed[3]);
    
      //color 1
    //if(Colors[0][0] != 0 && Colors[0][1] != 0 && Colors[0][2]){
      strip.setPixelColor((5+pixel1)%strip.numPixels(),Colors[0][2],Colors[0][1],Colors[0][0]);
      strip.setPixelColor((5+pixel1-8)%strip.numPixels(),0,0,0);
    //}
    
      //color 2
    strip.setPixelColor((pixel2+3)%strip.numPixels(),Colors[1][2],Colors[1][1],Colors[1][0]);
    strip.setPixelColor((pixel2+2)%strip.numPixels(),Colors[1][2],Colors[1][1],Colors[1][0]);
    strip.setPixelColor((pixel2+1)%strip.numPixels(),Colors[1][2],Colors[1][1],Colors[1][0]);
    strip.setPixelColor((pixel2-2)%strip.numPixels(),0,0,0);
    strip.setPixelColor((pixel2-3)%strip.numPixels(),0,0,0);
    strip.setPixelColor((pixel2-4)%strip.numPixels(),0,0,0);
      
      //color 3
    strip.setPixelColor((pixel3-3)%strip.numPixels(),Colors[2][2],Colors[2][1],Colors[2][0]);
    strip.setPixelColor((pixel3-2)%strip.numPixels(),Colors[2][2],Colors[2][1],Colors[2][0]);
    strip.setPixelColor((pixel3-1)%strip.numPixels(),Colors[2][2],Colors[2][1],Colors[2][0]);
    strip.setPixelColor((pixel3+2)%strip.numPixels(),0,0,0);
    strip.setPixelColor((pixel3+3)%strip.numPixels(),0,0,0);
    strip.setPixelColor((pixel3+4)%strip.numPixels(),0,0,0);
    
      //color 4
    strip.setPixelColor((pixel4-3)%strip.numPixels(),Colors[3][2],Colors[3][1],Colors[3][0]);
    strip.setPixelColor((pixel4-2)%strip.numPixels(),Colors[3][2],Colors[3][1],Colors[3][0]);
    strip.setPixelColor((pixel4-1)%strip.numPixels(),Colors[3][2],Colors[3][1],Colors[3][0]);
    strip.setPixelColor((pixel4+2)%strip.numPixels(),0,0,0);
    strip.setPixelColor((pixel4+3)%strip.numPixels(),0,0,0);
    strip.setPixelColor((pixel4+4)%strip.numPixels(),0,0,0);
    
    
    strip.show();
    delay(wait);
    
    if(AnalogInput[3] > 20)
        delay(int(AnalogInput[3]/8));
    
    
    if(i <! strip.numPixels()*10) // cycles of all 96 colors in the wheel
        i = 0;
      i++;
      
      check_Buttons();
  } while(Setting == 9);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////


void Strobe(uint8_t wait){
  int a=31, b=0, c=0;
  
  for(int x = 0; x <= 500; x++){
    
    for (int i = 0; i < strip.numPixels(); i++){
       strip.setPixelColor(i, b, c, a); //bgr
    }
    strip.show();   // write all the pixels out
    delay(wait);
    delay(50);
    //check_Buttons();
    //if(Setting != 3)
    //    break;
    
    if(x==0)
      b = 31;
    else if(x==1)
      c = 31;
    else if(x==2){
      a = 31;
      x = 0;
    }
  }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////


void Lighting(uint8_t wait){
  int y;
  
  for(int x=-15; x <= 15; x++){
    y = abs(x);
                     //   b,g,r
    strip.setPixelColor(101, 231-y, 231-y, 245-y);
    strip.setPixelColor(102, 236-y, 236-y, 250-y);
    strip.setPixelColor(103, 241-y, 241-y, 255-y);
    strip.setPixelColor(104, 236-y, 236-y, 250-y);
    strip.setPixelColor(105, 231-y, 231-y, 245-y);
    //delay(50);
    strip.show();   // write all the pixels out
    delay(wait);
    
    
    check_Buttons();
  }
  
  delay(500);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////


void test(uint8_t wait){
  int a = 0, b = 0, c = 0;
  
  for (int x = 0; x <= 60; x++){
   for (int i = 0; i < strip.numPixels(); i++){
     strip.setPixelColor(i, a, b, c); //bgr
   }
  strip.show();   // write all the pixels out
  delay(wait);
  delay(100);
  
  if(a < 31)
    a++;
  if(a > 15 && b < 31)
    b++;
  if(a > 15 && b > 15 && c < 31)
    c++;
  }
  
  a = 0;
  b = 0;
  c = 0;
  
  for (int x = 0; x <= 60; x++){
   for (int i = 0; i < strip.numPixels(); i++){
     strip.setPixelColor(i, b, c, a); //bgr
   }
  strip.show();   // write all the pixels out
  delay(wait);
  delay(100);
  
  if(a < 31)
    a++;
  if(a > 15 && b < 31)
    b++;
  if(a > 15 && b > 15 && c < 31)
    c++;
  }
  
  a = 0;
  b = 0;
  c = 0;
  
  for (int x = 0; x <= 60; x++){
   for (int i = 0; i < strip.numPixels(); i++){
     strip.setPixelColor(i, c, a, b); //bgr
   }
  strip.show();   // write all the pixels out
  delay(wait);
  delay(100);
  
  if(a < 31)
    a++;
  if(a > 15 && b < 31)
    b++;
  if(a > 15 && b > 15 && c < 31)
    c++;
  }
  
}



//                   DONE or sub-programs without any bugs
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

void check_Buttons(){
                                            Serial.println("check_Buttons");
  if(digitalRead(ShiftAll) == true){
    shiftIn();    //gets the value for the button(s) that was pushed
    
    if (Buttons[11] == 1) {
      Last_Button_Pushed = Setting;
      First = 1;
      Setting = 0;
    }
    else if(Buttons[10] == 1){
      Last_Button_Pushed = Setting;
      First = 1;
      Setting = 1;
    }
    else if(Buttons[8] == 1){
      Last_Button_Pushed = Setting;
      First = 1;
      Setting = 2;
    }
    else if(Buttons[3] == 1){
      Last_Button_Pushed = Setting;
      First = 1;
      Setting = 3;
    }
    else if(Buttons[15] == 1){
      Last_Button_Pushed = Setting;
      First = 1;
      Setting = 4;
    }
    else if(Buttons[9] == 1){
        Last_Button_Pushed = Setting;
        First = 1;
        Setting = 5;
    }
    else if(Buttons[7] == 1){
        Last_Button_Pushed = Setting;
        First = 1;
        Setting = 6;
    }
    else if(Buttons[2] == 1){
        Last_Button_Pushed = Setting;
        First = 1;
        Setting = 7;
    }
    else if(Buttons[14] == 1){
        Last_Button_Pushed = Setting;
        First = 1;
        Setting = 8;
    }
    else if(Buttons[12] == 1){
        Last_Button_Pushed = Setting;
        First = 1;
        Setting = 9;
    }
    else if(Buttons[5] == 1){
        Last_Button_Pushed = Setting;
        First = 1;
        Setting = 10;
    }
    else if(Buttons[1] == 1){
        Last_Button_Pushed = Setting;
        First = 1;
        Setting = 11;
    }
    else if(Buttons[13] == 1){
        Last_Button_Pushed = Setting;
        First = 1;
        Setting = 12;
    }
    else if(Buttons[6] == 1){
        Last_Button_Pushed = Setting;
        First = 1;
        Setting = 13;
    }
    else if(Buttons[4] == 1){
        Last_Button_Pushed = Setting;
        First = 1;
        Setting = 14;
    }
    else if(Buttons[0] == 1){
        Last_Button_Pushed = Setting;
        First = 1;
        Setting = 15;
    }
  }
  
  AnalogInput[0] = analogRead(AnalogPins[0]);
  AnalogInput[1] = analogRead(AnalogPins[1]);
  AnalogInput[2] = analogRead(AnalogPins[2]);
  AnalogInput[3] = analogRead(AnalogPins[3]);
  AnalogInput[4] = analogRead(AnalogPins[4]);
}



//                   Sub-programs for main funcions

unsigned int Wheel(byte WheelPos)
{
  byte r,g,b;
  switch(WheelPos >> 5)
  {
    case 0:
      r=31- WheelPos % 32;   //Red down
      g=WheelPos % 32;      // Green up
      b=0;                  //blue off
      break; 
    case 1:
      g=31- WheelPos % 32;  //green down
      b=WheelPos % 32;      //blue up
      r=0;                  //red off
      break; 
    case 2:
      b=31- WheelPos % 32;  //blue down 
      r=WheelPos % 32;      //red up
      g=0;                  //green off
      break;
  }
  return(Color(r,g,b));
}


unsigned int Wheel2(byte WheelPos, int Intencity)
{
  byte r,g,b;
  switch(WheelPos >> 5)
  {
    case 0:
      r= byte((31- WheelPos % 32)/Intencity);   //Red down
      g= byte((WheelPos % 32)/Intencity);      // Green up
      b=0;                  //blue off
      break; 
    case 1:
      g= byte((31- WheelPos % 32)/Intencity);  //green down
      b= byte((WheelPos % 32)/Intencity);      //blue up
      r=0;                  //red off
      break; 
    case 2:
      b= byte((31- WheelPos % 32)/Intencity);  //blue down 
      r= byte((WheelPos % 32)/Intencity);      //red up
      g=0;                  //green off
      break; 
  }
  return(Color(r,g,b));
}


unsigned int Color(byte r, byte g, byte b)
{
  //Take the lowest 5 bits of each value and append them end to end
  //Serial.println(((unsigned int)g & 0x1F )<<10 | ((unsigned int)b & 0x1F)<<5 | (unsigned int)r & 0x1F);
  return( ((unsigned int)g & 0x1F )<<10 | ((unsigned int)b & 0x1F)<<5 | (unsigned int)r & 0x1F);
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


