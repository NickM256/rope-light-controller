#include <TimerOne.h> //used by the strip to send pixel clocks
#include "LPD6803.h"

  //pins
const int dataPin = 5;       // 'yellow' wire
const int clockPin = 4;      // 'ornge' wire

  //variables
int color[3]={255,0,0};
int Num_color = 0;


LPD6803 strip = LPD6803(100, dataPin, clockPin);

void setup() {
  //Serial.begin(9600);
  
  // The Arduino needs to clock out the data to the pixels
  // this happens in interrupt timer 1, we can change how often
  // to call the interrupt. setting CPUmax to 100 will take nearly all the
  // time to do the pixel updates and a nicer/faster display, 
  // especially with strands of over 100 dots.
  // (Note that the max is 'pessimistic', its probably 10% or 20% less in reality)
  strip.setCPUmax(50);  // start with 50% CPU usage. up this if the strand flickers or is slow
  
  // Start up the LED counter
  strip.begin();

  // Update the strip, to start they are all 'off'
  strip.show();
}

void loop(){
  knight_rider(50);
}


void knight_rider(uint8_t wait) {
  //strip.setPixelColor(pixil location, color);   color in a streem of bits
  //strip.setPixelColor(pixil location, red, green, blue);
  //strip.numPixels()   gives the number of pixels (50 if there are 50 pixels)
  
  int last_pixel=strip.numPixels()-1;
  for(int i=0; i < strip.numPixels(); i++){
    strip.setPixelColor(i,color[0],color[1],color[2]);
    strip.setPixelColor(last_pixel,0,0,0);
    strip.show();
    delay(wait);
    last_pixel=i;
  }
  for(int j=strip.numPixels()-1; j > 0; j--){
    strip.setPixelColor(j,color[0],color[1],color[2]);
    strip.setPixelColor(last_pixel,0,0,0);
    strip.show();
    delay(wait);
    last_pixel=j;
  }


  switch(Num_color){
    case(0):
      color[0] = 255;
      color[1] = 255;
      color[2] = 0;
      break;
    case(1):
      color[0] = 0;
      color[1] = 255;
      color[2] = 0;
      break;
    case(2):
      color[0] = 0;
      color[1] = 255;
      color[2] = 255;
      break;
    case(3):
      color[0] = 255;
      color[1] = 255;
      color[2] = 255;
      break;
    case(4):
      color[0] = 255;
      color[1] = 0;
      color[2] = 255;
      break;
    case(5):
      color[0] = 0;
      color[1] = 0;
      color[2] = 255;
      break;
    default:
      color[0] = 255;
      color[1] = 0;
      color[2] = 0;
      Num_color=0;
      break;
    //Serial.println(color[0]);
    //Serial.println(color[1]);
    //Serial.println(color[2]);
  }
  Num_color=Num_color+1;
}




// Creates a 15 bit color value from R,G,B
unsigned int Color(byte r, byte g, byte b) //receives a value 0 to 31
{
  //Take the lowest 5 bits of each value and append them end to end
  return( ((unsigned int)g & 0x1F )<<10 | ((unsigned int)b & 0x1F)<<5 | (unsigned int)r & 0x1F);
}



