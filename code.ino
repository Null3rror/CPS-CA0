// include Arduino stepper motor library
#include <Stepper.h>
 
// change this to the number of steps on your motor
#define STEPS 20
 

const int in1 = 8;
const int in2 = 9;
const int in3 = 10;
const int in4 = 11;

// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to
Stepper stepper(STEPS, in1, in2, in3, in4);
 
const int stopButton         =  6; // direction control button is connected to Arduino pin 6
const int clockwiseButton    =  5; // direction control button is connected to Arduino pin 5
const int antiClockwisButton =  4; // direction control button is connected to Arduino pin 4




 
void setup()
{
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  // configure button pin as input with internal pull up enabled
  pinMode(stopButton, INPUT_PULLUP);
  pinMode(clockwiseButton, INPUT_PULLUP);
  pinMode(antiClockwisButton, INPUT_PULLUP);
}
 
int direction_ = 1, speed_ = 0;
 
void loop()
{
  
  if ( digitalRead(stopButton) == 0 ) {
    speed_ = 0;
  }
  else {
    speed_ = 255;
  }
  stepper.setSpeed(speed_);
  
  
  // if button is pressed
//    if ( debounce() )  // debounce button signal
//    {
//      direction_ *= -1;  // reverse direction variable
//      while ( debounce() ) ;  // wait for button release
//    }
 
  
  int val = 10;
 
  // map digital value from [0, 1023] to [5, 100]
  // ===> min speed = 5 and max speed = 100 rpm
//  if ( speed_ != map(val, 0, 1023, 5, 100) )
//  { // if the speed was changed
//    speed_ = map(val, 0, 1023, 5, 100);
//    // set the speed of the motor
//    stepper.setSpeed(speed_);
//  }
 
  // move the stepper motor
  stepper.step(direction_);
 
}

void stopMoving() { // TODO: better name
  
}
 
//// a small function for button debounce
//bool debounce()
//{
//  byte count = 0;
//  for(byte i = 0; i < 5; i++) {
//    if (digitalRead(button) == 0)
//      count++;
//    delay(10);
//  }
//  if(count > 2)  return 1;
//  else           return 0;
//}
