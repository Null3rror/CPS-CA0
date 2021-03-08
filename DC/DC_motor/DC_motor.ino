// Arduino DC motor speed and direction control
 
#define DIR_BUTTON          5  //CHANGE DIRECTION BUTTON
#define ANTI_CLOCKWISE           9 //ANTI CLOCKWISE DIRECTION 
#define CLOCKWISE                10 //CLOCKWISE DIRECTION 
#define INCREASE_BUTTON     4  //INCREASE MOTOR SPEED BUTTON
#define DECREASE_BUTTON     3  //DECREASE MOTOR SPEED BUTTON
#define STOP_START_BUTTON   2  //STOP and START BUTTON
 
boolean motorDir         =  0;
boolean stopStatus       =  0;
boolean changeStatus     =  0;
int pwmValue;
 
void setup() {
  Serial.begin(9600);
 
  pinMode(DIR_BUTTON, INPUT_PULLUP);
  pinMode(INCREASE_BUTTON, INPUT_PULLUP);
  pinMode(STOP_START_BUTTON, INPUT_PULLUP);
  pinMode(DECREASE_BUTTON, INPUT_PULLUP);  
 
  pinMode(ANTI_CLOCKWISE, OUTPUT);
  pinMode(CLOCKWISE, OUTPUT);

  pwmValue = 255;
  Serial.println("start pwm : " +  String(pwmValue));
}
 
void loop() {

  if(!digitalRead(STOP_START_BUTTON)){
   while(!digitalRead(STOP_START_BUTTON)); 
   
   stopStatus = !stopStatus;                
  }
 
  if(stopStatus){
   digitalWrite(ANTI_CLOCKWISE, 0);
   digitalWrite(CLOCKWISE, 0);
  }else{
    if(!digitalRead(INCREASE_BUTTON)){              
      while(!digitalRead(INCREASE_BUTTON));
     
      pwmValue = pwmValue  + 10;
      changeStatus = 1;
    }
   
    if(!digitalRead(DECREASE_BUTTON)){              
      while(!digitalRead(DECREASE_BUTTON));     
      
      pwmValue = pwmValue  - 10;
      changeStatus = 1;
    }
   
    if(pwmValue > 255){
      pwmValue = 255;
      changeStatus = 1;
    }else if(pwmValue < 0){
      pwmValue = 0;
      changeStatus = 1;
    }
   
    if(changeStatus){
      Serial.println("current pwm : " + String(pwmValue));
      changeStatus = 0;
    }  
   
    if(motorDir)
      analogWrite(ANTI_CLOCKWISE, pwmValue);
    else
      analogWrite(CLOCKWISE, pwmValue);


    if(!digitalRead(DIR_BUTTON)){              
     while(!digitalRead(DIR_BUTTON));  
     
     motorDir = !motorDir;               
     if(motorDir)
       digitalWrite(CLOCKWISE, 0);
     else
       digitalWrite(ANTI_CLOCKWISE, 0);
    }
  }
}
