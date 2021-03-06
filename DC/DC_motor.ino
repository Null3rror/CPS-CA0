// Arduino DC motor speed and direction control
 
#define button   5
#define pot      0
#define pwm1     9
#define pwm2    10
#define increase 4
#define decrease 3
#define stop_start 2
 
boolean motor_dir = 0;
boolean stopb=0;
boolean flag =0;
int motor_speed;

 
void setup() {
  Serial.begin(9600);
  pinMode(button, INPUT_PULLUP);
  pinMode(increase , INPUT_PULLUP);
  pinMode(stop_start , INPUT_PULLUP);
  pinMode(decrease, INPUT_PULLUP);  
  pinMode(pwm1,   OUTPUT);
  pinMode(pwm2,   OUTPUT);

motor_speed = analogRead(pot) / 4;
Serial.println("start pwm : " +  String(motor_speed));
}
 
void loop() {

   if(!digitalRead(stop_start)){                // If direction button is pressed
    while(!digitalRead(stop_start));           // Wait until direction button released
    stopb = !stopb;                // Toggle direction variable
  }
    if(stopb){
    digitalWrite(pwm1, 0);
    digitalWrite(pwm2, 0);
    }
    else{

  if(!digitalRead(increase)){              
    while(!digitalRead(increase));     
  motor_speed = motor_speed  + 10;
  flag =1;
}
  if(!digitalRead(decrease)){              
    while(!digitalRead(decrease));     
  motor_speed = motor_speed  - 10;
  flag =1;
}
  if(motor_speed > 255){
    motor_speed = 255;
    flag =1;
  }else if(motor_speed < 0){
    motor_speed = 0;
    flag =1;

}
if(flag){
  Serial.println("current pwm : " + String(motor_speed));
  flag =0;
}  
if(motor_dir)
    analogWrite(pwm1, motor_speed);
  else
    analogWrite(pwm2, motor_speed);
  

  if(!digitalRead(button)){                // If direction button is pressed
    while(!digitalRead(button));           // Wait until direction button released
    motor_dir = !motor_dir;                // Toggle direction variable
    if(motor_dir)
      digitalWrite(pwm2, 0);
    else
      digitalWrite(pwm1, 0);
  }
    }
}
