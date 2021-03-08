#include <Stepper.h>
#define STEPS 36 // total number of steps this motor can take
 

const int IN1 = 8;
const int IN2 = 9;
const int IN3 = 10;
const int IN4 = 11;

Stepper stepper(STEPS, IN1, IN2, IN3, IN4);

const int STOP_BUTTON           =  6; // motorDirection control button is connected to Arduino pin 6
const int CLOCKWISE_BUTTON      =  5; // motorDirection control button is connected to Arduino pin 5
const int ANTI_CLOCKWISE_BUTTON =  4; // motorDirection control button is connected to Arduino pin 4

boolean stopStatus;
boolean stopPrevStatus;

int motorDirection = 1, rpm;
int prevDirection = 1;
 

void setup()
{
  stopStatus = false;
  stopPrevStatus = stopStatus;
  prevDirection = motorDirection;
  rpm = 6;
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  // configure button pin as input with internal pull up enabled
  pinMode(STOP_BUTTON, INPUT_PULLUP);
  pinMode(CLOCKWISE_BUTTON, INPUT_PULLUP);
  pinMode(ANTI_CLOCKWISE_BUTTON, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop()
{ 
  if (!digitalRead(STOP_BUTTON)) { // button down
    while(!digitalRead(STOP_BUTTON)); // loop until button down, exit when button is up
    stopStatus = true;
  }
  if (!digitalRead(CLOCKWISE_BUTTON)) {
    while(!digitalRead(CLOCKWISE_BUTTON));
    stopStatus = false;
    motorDirection = 1;
  }
  if (!digitalRead(ANTI_CLOCKWISE_BUTTON)) {
    while(!digitalRead(ANTI_CLOCKWISE_BUTTON));
    stopStatus = false;
    motorDirection = -1;
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
    stepper.step(motorDirection);
  }
  stopPrevStatus = stopStatus;
  prevDirection = motorDirection;

}

boolean HasStopStatusChanged() {
  return stopStatus != stopPrevStatus;
}

boolean HasDirChanged() {
  return motorDirection != prevDirection;
}


void PrintStopStatus() {
  Serial.println(stopStatus ? "Paused" : "UnPaused"); 
}

void PrintDir() {
  Serial.print("motorDirection: ");
  Serial.println(motorDirection > 0 ? "Clockwise" : "AntiClockwise");
}
