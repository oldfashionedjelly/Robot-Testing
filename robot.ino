#include <PWMServo.h>
#define IN1 7
#define IN2 8
#define ENA 5  

#define FRONT 96 //if left: increase; if right: decrease
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
#define TURN_PERIOD   1400
#define TEMP_PERIOD   380
#define TEMP_TURN_PERIOD 680

#define SERVO_STEER   9

// kedaar wuz here

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

void right(int angle, int period, int speed) {
    forward(speed, period*0.3);
    turn(angle);
    delay(2000);
    forward(speed, period);
    turn(FRONT-10);
    delay(2000);
    back(speed, period*0.25);
}

void backRight(int angle, int period, int speed) {
     forward(speed,period*0.25);
     delay(2000);
     turn(angle);
     back(speed, period);
     delay(2000);
     turn(FRONT-10);
     back(speed, period*0.3);
}

void left() {
  
}

void backLeft() {
  
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

    right(RIGHT, TEMP_TURN_PERIOD, TEMP_SPEED);
}

 
void loop() {
    
}