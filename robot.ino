#include <PWMServo.h>
#define IN1 7
#define IN2 8
#define ENA 5  

#define FRONT 96 //if left: increase; if right: decrease
int  RIGHT=FRONT+45;
int  LEFT=FRONT-45;

#define SENSOR_FRONT 90
int SENSOR_LEFT=SENSOR_FRONT+25;
int SENSOR_RIGHT=SENSOR_FRONT-25;
int SENSOR_FAR_LEFT=SENSOR_FRONT+60;
int SENSOR_FAR_RIGHT=SENSOR_FRONT-60;

#define DELAY_TIME    1000   

#define LOW_SPEED     140
#define FAST_SPEED    240 
#define MID_SPEED     190

#define TURN_SPEED    200
#define TURN_PERIOD   1400

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

int period = 325;
bool stopped = false; 

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
    stopped = true;
    stop();
}

void turn(int angle) {
  head_steer.write(angle);
}

void turn90(int angle, int period, int speed) {
    head_steer.write(angle);
    forward(speed, period);
}
 
void stop() {

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
    Serial.begin(9600);

    turn(FRONT);
    stop();
    delay(2000);
    
    turn90(LEFT, TURN_PERIOD, TURN_SPEED);
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