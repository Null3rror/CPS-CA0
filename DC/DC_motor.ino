// Arduino DC motor speed and direction control
 
#define DIR_BUTTON          5  //CHANGE DIRECTION BUTTON
#define POT                 0 
#define PWM1                9
#define PWM2                10
#define INCREASE_BUTTON     4  //INCREASE MOTOR SPEED BUTTON
#define DECREASE_BUTTON     3  //DECREASE MOTOR SPEED BUTTON
#define STOP_START_BUTTON   2  //STOP and START BUTTON
 
boolean motorDir         =  0;
boolean stopStatus       =  0;
boolean changeStatus     =  0;
int pwmAnalogeValue;
 
void setup() {
  Serial.begin(9600);
 
  pinMode(DIR_BUTTON, INPUT_PULLUP);
  pinMode(INCREASE_BUTTON, INPUT_PULLUP);
  pinMode(STOP_START_BUTTON, INPUT_PULLUP);
  pinMode(DECREASE_BUTTON, INPUT_PULLUP);  
 
  pinMode(PWM1, OUTPUT);
  pinMode(PWM2, OUTPUT);

  pwmAnalogeValue = analogRead(POT) / 4;
  Serial.println("start pwm : " +  String(motorSpeed));
}
 
void loop() {

  if(!digitalRead(STOP_START_BUTTON)){
   while(!digitalRead(STOP_START_BUTTON)); 
   
   stopStatus = !stopStatus;                
  }
 
  if(stopStatus){
   digitalWrite(PWM1, 0);
   digitalWrite(PWM2, 0);
  }else{
    if(!digitalRead(INCREASE_BUTTON)){              
      while(!digitalRead(INCREASE_BUTTON));
     
      pwmAnalogeValue = pwmAnalogeValue  + 10;
      changeStatus = 1;
    }
   
    if(!digitalRead(DECREASE_BUTTON)){              
      while(!digitalRead(DECREASE_BUTTON));     
      
      pwmAnalogeValue = pwmAnalogeValue  - 10;
      changeStatus = 1;
    }
   
    if(pwmAnalogeValue > 255){
      pwmAnalogeValue = 255;
      changeStatus = 1;
    }else if(pwmAnalogeValue < 0){
      pwmAnalogeValue = 0;
      changeStatus = 1;
    }
   
    if(flag){
      Serial.println("current pwm : " + String(pwmAnalogeValue));
      changeStatus = 0;
    }  
   
    if(motorDir)
      analogWrite(PWM1, pwmAnalogeValue);
    else
      analogWrite(PWM2, pwmAnalogeValue);


    if(!digitalRead(DIR_BUTTON)){              
     while(!digitalRead(DIR_BUTTON));  
     
     motorDir = !motorDir;               
     if(motorDir)
       digitalWrite(PWM2, 0);
     else
       digitalWrite(PWM1, 0);
    }
  }
}
