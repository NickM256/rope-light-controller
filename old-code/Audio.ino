int analogPin = 5;     // potentiometer wiper (middle terminal) connected to analog pin 3
                       // outside leads to ground and +5V
int val = 0;           // variable to store the value read
int valreal = 0;
int valpre = 0;
int maxval = 0;
void setup()
{
  //Serial.begin(9600);          //  setup serial
}

void loop()
{
  valreal = analogRead(analogPin);    // read the input pin
  val = (valreal*2+valpre)/3;
  valpre=valreal;
  
  if (val > maxval)
    maxval=(val+maxval)/2;
  //Serial.println(val);
  map(val,0,maxval,0,100);
  if (val<50)
    val=0;
  
  //analogWrite(11,val);
  //analogWrite(9,val);
  analogWrite(6,val);
}
