#include <PWMServo.h>
#define IN1 7
#define IN2 8
#define ENA 5  

#define FRONT 94 //if left: increase; if right: decrease
int  RIGHT=FRONT+45;
int  LEFT=FRONT-45;

#define DELAY_TIME    1000   

#define LOW_SPEED     140
#define MID_SPEED     190
#define FAST_SPEED    240 
#define TURN_SPEED    200
#define TEMP_SPEED    255

#define LOW_PERIOD    833
#define MID_PERIOD    525
#define FAST_PERIOD   325
#define TEMP_PERIOD   380

#define TURN_PERIOD   1400
#define TEMP_TURN_PERIOD 730

#define SERVO_STEER   9  

PWMServo head_steer;

void back(int speed, int period) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2,LOW);
    analogWrite(ENA,speed);
    delay(period);
    stop();
}
 
void forward(int speed, int period)  {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2,HIGH);
    analogWrite(ENA,speed);
    delay(period);
    stop();
}

void turn(int angle) {
  head_steer.write(angle);
}

void right(int speed, int period) {
    forward(speed, period*0.3);
    delay(2000);
    turn(RIGHT);
    delay(2000);
    forward(speed, period);
    delay(2000);
    turn(FRONT-10);
    delay(2000);
    back(speed, period*0.15);
    turn(FRONT);
}

void backRight(int speed, int period) {
     forward(speed,period*0.15);
     delay(2000);
     turn(RIGHT);
     delay(2000);
     back(speed, period);
     delay(2000);
     turn(FRONT-10);
     delay(2000);
     back(speed, period*0.3);
     turn(FRONT);
}

void left(int speed, int period) {
     back(speed, period*0.25);
     delay(2000);
     turn(LEFT);
     delay(2000);
     forward(speed, period-60);
     delay(2000);
     turn(RIGHT);
     delay(2000);
     back(speed, period*0.35);
     delay(2000);
     turn(FRONT-10);
     delay(2000);
     back(speed, period*0.2);
     turn(FRONT);
}

void backLeft(int speed, int period) {
  forward(speed, period*0.2);
  delay(2000);
  turn(RIGHT);
  delay(2000);
  forward(speed, period*0.5);
  delay(2000);
  turn(LEFT);
  delay(2000);
  back(speed, period-110);
  delay(2000);
  turn(RIGHT);
  delay(2000);
  forward(speed, period*0.6);
  delay(2000);
  turn(FRONT);
  delay(2000);
  back(speed, period*0.25);
}
 
void stop() {
    analogWrite(ENA,0);
}

  
void setup() {
    pinMode(ENA, OUTPUT); 
    pinMode(IN1, OUTPUT); 
    pinMode(IN2, OUTPUT); 

    
    head_steer.attach(SERVO_STEER);
    Serial.begin(9600);

    turn(FRONT);
    stop();
    delay(2000);


}

 
void loop() {
    
}