#include <PWMServo.h>
#define IN1 7
#define IN2 8
#define ENA 5  

#define FRONT 90
int SHARP_RIGHT=FRONT+35;
int SHARP_LEFT=FRONT-35;
int  RIGHT=FRONT+18;
int  LEFT=FRONT-18;

#define SENSOR_FRONT 90
int SENSOR_LEFT=SENSOR_FRONT+25;
int SENSOR_RIGHT=SENSOR_FRONT-25;
int SENSOR_FAR_LEFT=SENSOR_FRONT+60;
int SENSOR_FAR_RIGHT=SENSOR_FRONT-60;

#define DELAY_TIME    1000   

#define SPEED         170
#define FAST_SPEED    230 
#define MID_SPEED     200
#define SERVO_STEER   9  
#define SERVO_SENSOR  10  

#define Echo_PIN    2 
#define Trig_PIN    3 

PWMServo head;
PWMServo head_steer;

int leftscanval, centerscanval, rightscanval, ldiagonalscanval, rdiagonalscanval;
const int distancelimit = 30;  //cm
const int sidedistancelimit = 30; 
int distance;


void back(int speed) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2,LOW);
    analogWrite(ENA,speed);
}
 
void forward(int speed)  {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2,HIGH);
    analogWrite(ENA,speed);
}
 
void turn(int angle) {
    head_steer.write(angle);
}
 
void stop() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2,LOW);
    analogWrite(ENA,0);
}

  
void setup() {
    pinMode(ENA, OUTPUT); 
    pinMode(IN1, OUTPUT); 
    pinMode(IN2, OUTPUT); 
    pinMode(Trig_PIN, OUTPUT); 
    pinMode(Echo_PIN,INPUT); 
    
    head_steer.attach(SERVO_STEER);
    head.attach(SERVO_SENSOR); 
    head.write(90);
    turn(FRONT);
    stop();
    delay(2000);

    Serial.begin(9600);
}

 
void loop() {
    
}

int watch() {
  long echo_distance;
  digitalWrite(Trig_PIN,LOW);
  delayMicroseconds(5);                                                                              
  digitalWrite(Trig_PIN,HIGH);
  delayMicroseconds(15);
  digitalWrite(Trig_PIN,LOW);
  echo_distance=pulseIn(Echo_PIN,HIGH);
  echo_distance=echo_distance*0.01657; //cm
  return round(echo_distance);
}

String watchsurrounding() {
    int obstacle_status =B100000;
    centerscanval = watch();
    if(centerscanval<distancelimit){
        stop();
        obstacle_status = obstacle_status | B100;
    }

    head.write(SENSOR_LEFT);
    delay(100);
    ldiagonalscanval = watch();
    if(ldiagonalscanval<distancelimit){
        stop();
        obstacle_status = obstacle_status | B1000;
    }

    head.write(SENSOR_FAR_LEFT); 
    delay(300);
    leftscanval = watch();
    if(leftscanval<sidedistancelimit){
        stop();
        obstacle_status = obstacle_status | B10000;
    }

    head.write(SENSOR_FRONT); 
    delay(100);
    centerscanval = watch();
    if(centerscanval<distancelimit){
        stop();
        obstacle_status = obstacle_status | B100;
    }

    head.write(SENSOR_RIGHT);
    delay(100);
    rdiagonalscanval = watch();
    if(rdiagonalscanval<distancelimit){
        stop();
        obstacle_status = obstacle_status | B10;
    }
  
    head.write(SENSOR_FAR_RIGHT);
    delay(100);
    rightscanval = watch();
    if(rightscanval<sidedistancelimit){
        stop();
        obstacle_status = obstacle_status | 1;
    }

    head.write(SENSOR_FRONT);
    delay(300);
    String obstacle_str= String(obstacle_status,BIN);
    obstacle_str= obstacle_str.substring(1,6);
  
    return obstacle_str; 
}