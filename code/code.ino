#include <Stepper.h>
#define STEPS 36
 

const int in1 = 8;
const int in2 = 9;
const int in3 = 10;
const int in4 = 11;

Stepper stepper(STEPS, in1, in2, in3, in4);
 
const int stopButton         =  6; // direction control button is connected to Arduino pin 6
const int clockwiseButton    =  5; // direction control button is connected to Arduino pin 5
const int antiClockwisButton =  4; // direction control button is connected to Arduino pin 4

boolean stopStatus;
boolean stopPrevStatus;


 
int direction_ = 1, rpm;
int prevDirection = 1;
 

void setup()
{
  stopStatus = false;
  stopPrevStatus = stopStatus;
  prevDirection = direction_;
  rpm = 10;
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  // configure button pin as input with internal pull up enabled
  pinMode(stopButton, INPUT_PULLUP);
  pinMode(clockwiseButton, INPUT_PULLUP);
  pinMode(antiClockwisButton, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop()
{ 
  if (!digitalRead(stopButton)) { // button down
    while(!digitalRead(stopButton)); // loop until button down, exit when button is up
    stopStatus = true;
  }
  if (!digitalRead(clockwiseButton)) {
    while(!digitalRead(clockwiseButton));
    stopStatus = false;
    direction_ = 1;
  }
  if (!digitalRead(antiClockwisButton)) {
    while(!digitalRead(antiClockwisButton));
    stopStatus = false;
    direction_ = -1;
  }

  if (HasStopStatusChanged()) {
    PrintStopStatus();
  }

  if (HasDirChanged()) {
    PrintDir();
  }
  
  stepper.setSpeed(rpm);

  if (!stopStatus) {
    // move the stepper motor
    stepper.step(direction_);
  }
  stopPrevStatus = stopStatus;
  prevDirection = direction_;

}

boolean HasStopStatusChanged() {
  return stopStatus != stopPrevStatus;
}

boolean HasDirChanged() {
  return direction_ != prevDirection;
}


void PrintStopStatus() {
  Serial.println(stopStatus ? "Paused" : "UnPaused"); 
}

void PrintDir() {
  Serial.print("direction: ");
  Serial.println(direction_ > 0 ? "clockwise" : "antiClockwise");
}
