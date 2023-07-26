// Spherical Manipulator

//IR
#include <IRremote.h> 
const int IRpin = 7;
IRrecv IR(IRpin);


//LEFT DC MOTOR
const int dir1 = 2;
const int dir2 = 4;
const int speed1 = 3;

//RIGHT DC Motor  
const int dir3 = 8;
const int dir4 = 12; 
const int speed2 = 9;

//MOTOR SPEED
int MOTSPEED1 = 255;
int MOTSPEED2 = 0;

//ULTRASONIC SENSOR
const int TRIGGER = 5;
const int ECHO = 6;
long Duration; 
int Distance; 
const int DistanceStop = 10;//DISTANCE WHERE CAR STOPS 

//DELAY TIME
int t = 100; 
 
void setup() {

Serial.begin(9600);
//IR SENSOR
IR.enableIRIn();
//LEFT MOTOR
pinMode(dir1,OUTPUT); 
pinMode(dir2,OUTPUT); 
pinMode(speed1,OUTPUT); 
//RIGHT MOTOR
pinMode(dir3,OUTPUT); 
pinMode(dir4,OUTPUT); 
pinMode(speed2,OUTPUT); 
//ULTRASONIC SENSOR
pinMode(TRIGGER, OUTPUT);
pinMode(ECHO, INPUT);

}

void loop() {
digitalWrite(TRIGGER, LOW);
delayMicroseconds(10);
 
digitalWrite(TRIGGER, HIGH); 
delayMicroseconds(10);
digitalWrite(TRIGGER, LOW);

Duration = pulseIn(ECHO, HIGH);
Distance = (Duration * 0.0343/2);//CALCULATION FOR DISTANCE

if (Distance <= DistanceStop)//IF THE DISTANCE IS LOWER THAN 10CM
{
//CAR STOPS  
digitalWrite(dir1, LOW);
digitalWrite(dir2, LOW);
digitalWrite(dir3, LOW); 
digitalWrite(dir4, LOW);
analogWrite(speed1,MOTSPEED1);
analogWrite(speed2,MOTSPEED1);
}

else{
  while (IR.decode()){
  if(IR.decodedIRData.decodedRawData == 0xE718FF00){ //UP BUTTON IS PRESSED
    //CAR MOVES FORWARD
    digitalWrite(dir1, HIGH);
    digitalWrite(dir2, LOW);
    digitalWrite(dir3, LOW);
    digitalWrite(dir4, HIGH);
    analogWrite(speed1, MOTSPEED1);
    analogWrite(speed2, MOTSPEED1);
  }
  else if(IR.decodedIRData.decodedRawData == 0xAD52FF00){ //DOWN BUTTON IS PRESSED
    //CAR MOVES BACKWARD
    digitalWrite(dir1, LOW);
    digitalWrite(dir2, HIGH);
    digitalWrite(dir3, HIGH);
    digitalWrite(dir4, LOW);
    analogWrite(speed1, MOTSPEED1);
    analogWrite(speed2, MOTSPEED1);
  }
  else if(IR.decodedIRData.decodedRawData == 0xE31CFF00){ //OK BUTTON IS PRESSED
    //CAR STOP
    digitalWrite(dir1, LOW);
    digitalWrite(dir2, LOW);
    digitalWrite(dir3, LOW);
    digitalWrite(dir4, LOW);
    analogWrite(speed1, MOTSPEED2);
    analogWrite(speed2, MOTSPEED2);
  }
  else if(IR.decodedIRData.decodedRawData == 0XF708FF00){ //LEFT BUTTON IS PRESSED
    //CAR ROTATES LEFT
    digitalWrite(dir1, LOW);
    digitalWrite(dir2, HIGH);
    digitalWrite(dir3, LOW);
    digitalWrite(dir4, HIGH);
    analogWrite(speed1, MOTSPEED1);
    analogWrite(speed2, MOTSPEED1);
  }
  else if(IR.decodedIRData.decodedRawData == 0XA55AFF00){ //RIGHT BUTTON IS PRESSED
      //CAR ROTATES RIGHT
      digitalWrite(dir1, HIGH);
      digitalWrite(dir2, LOW);
      digitalWrite(dir3, HIGH);
      digitalWrite(dir4, LOW);
      analogWrite(speed1, MOTSPEED1);
      analogWrite(speed2, MOTSPEED1);
    }
    IR.resume();
    delay(50);//DELAY TIME  
} 
}

}