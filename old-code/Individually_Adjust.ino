#include <TimerOne.h> //used by the strip to send pixel clocks
#include "LPD6803.h"

int dataPin = 10;       // 'yellow' wire
int clockPin = 12;      // 'ornge' wire
int pixel_state= 0;

// Init our Vars
int RedValue;
int GreenValue;
int BlueValue;
int buttonState;
boolean hold = false;

const int redPin = 11;
const int greenPin = 10;
const int bluePin = 9;

LPD6803 strip = LPD6803(49, dataPin, clockPin);

void setup() {
  //Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(2, INPUT);
  
  // The Arduino needs to clock out the data to the pixels
  // this happens in interrupt timer 1, we can change how often
  // to call the interrupt. setting CPUmax to 100 will take nearly all all the
  // time to do the pixel updates and a nicer/faster display, 
  // especially with strands of over 100 dots.
  // (Note that the max is 'pessimistic', its probably 10% or 20% less in reality)
  
  strip.setCPUmax(50);  // start with 50% CPU usage. up this if the strand flickers or is slow
  
  // Start up the LED counter
  strip.begin();

  // Update the strip, to start they are all 'off'
  strip.show();
}


void loop() {
  
  //strip.setPixelColor(pixil location, color); color in a streem of bits
  
  
  buttonState = digitalRead(2);
  
  if(buttonState == 1 && hold == false){
    pixel_state = pixel_state + 1;
    if (pixel_state == strip.numPixels())
      pixel_state = 0;
    hold = true;
    Serial.println(pixel_state);
    Serial.println(get_value());
  }
  else if(buttonState == 0){
    hold = false;
  }
  
  print_LED(50);
}


void print_LED(uint8_t wait){
  strip.setPixelColor(pixel_state, get_value());
  strip.show();
  delay(wait);
}

// Create a 15 bit color value from R,G,B
unsigned int Color(byte r, byte g, byte b)
{
  //Take the lowest 5 bits of each value and append them end to end
  return( ((unsigned int)g & 0x1F )<<10 | ((unsigned int)b & 0x1F)<<5 | (unsigned int)r & 0x1F);
}


unsigned int get_value()
{
  byte r; 
  byte g;
  byte b;
  // Read the voltage on each analog pin then scale down to 0-255 and inverting the value for common anode
  RedValue = (1024 - analogRead(0));
  BlueValue = (1024 - analogRead(1));
  GreenValue = (1024 - analogRead(2));
 
// Write the color to each pin using PWM and the value gathered above
  if(RedValue <= 160)
    RedValue = 160;
  else if(RedValue >= 865)
    RedValue = 865;
  
  if(BlueValue <= 160)
    BlueValue = 160;
  else if(BlueValue >= 865)
    BlueValue = 865;

  if(GreenValue <= 160)
    GreenValue = 160;
  else if(GreenValue >= 865)
    GreenValue = 865;
    
    //RedValue = RedValue - 160;
    //BlueValue = BlueValue - 160;
    //GreenValue = GreenValue - 160;
    
    RedValue = map( RedValue, 160, 865, 0, 31 );
    BlueValue = map( BlueValue, 160, 865, 0, 31 );
    GreenValue = map( GreenValue, 160, 865, 0, 31 );
    
    return(Color(RedValue, GreenValue, BlueValue));
}
