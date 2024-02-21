#include <movingAvg.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <Wire.h>

Adafruit_BNO055 bno = Adafruit_BNO055(55);

//Constants:
//const int ledPin1 = 2;   //pin 2
//const int ledPin2 = 3;   //pin 3
const int flexPin1 = A0; //pin A0 to read analog input
const int flexPin2 = A1;  //pin A1 to read analog input
const int flexPin3 = A2;  //pin A2 to read analog input
const int flexPin4 = A3;  //pin A3 to read analog input
const int flexPin5 = A6;  //pin A4 to read analog input


//Variables:
int value1; //save analog value for sensor 1
int value2; //save analog value for sensor 2
int value3; //save analog value for sensor 3
int value4; //save analog value for sensor 4
int value5; //save analog value for sensor 5

movingAvg myIndex(10);
movingAvg myThumb(10);
movingAvg myMiddle(10);
movingAvg myRing(10);
movingAvg myPinky(10);

int cal_thumb;
int cal_ind;
int cal_mid;
int cal_ring;
int cal_pin;


void setup(){
 
 // pinMode(ledPin1, OUTPUT);  //Set pin 2 as 'output'
 // pinMode(ledPin2, OUTPUT);  //Set pin 3 as 'output'


  Serial.begin(9600);       //Begin serial communication
  myIndex.begin();
  myThumb.begin();
  myMiddle.begin();
  myRing.begin();
  myPinky.begin();

  for(int i = 0; i < 100; i++){
    myThumb.reading(analogRead(flexPin1));
    myIndex.reading(analogRead(flexPin2));
    myMiddle.reading(analogRead(flexPin3));
    myRing.reading(analogRead(flexPin4));
    myPinky.reading(analogRead(flexPin5));
  }
  cal_thumb = myThumb.getAvg();
  cal_ind = myIndex.getAvg();
  cal_mid = myMiddle.getAvg();
  cal_ring = myRing.getAvg();
  cal_pin = myPinky.getAvg();
  myThumb.reset();
  myIndex.reset();
  myMiddle.reset();
  myRing.reset();
  myPinky.reset();

  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
 
  delay(1000);
   
  bno.setExtCrystalUse(true);
}


void loop(){
  sensors_event_t event;
  bno.getEvent(&event);
  value1 = analogRead(flexPin1) - cal_thumb/*calibrated_full_open*/;         //Read and save analog value from flex sensor 1
  value2 = analogRead(flexPin2) - cal_ind;         //Read and save analog value from flex sensor 2
  value3 = analogRead(flexPin3) - cal_mid;         //Read and save analog value from flex sensor 3
  value4 = analogRead(flexPin4) - cal_ring;         //Read and save analog value from flex sensor 4
  value5 = analogRead(flexPin5) - cal_pin;         //Read and save analog value from flex sensor 5

  Serial.println((String) myThumb.reading(value1) + "," + myIndex.reading(value2) + "," + myMiddle.reading(value3) + "," + myRing.reading(value4) + "," + myPinky.reading(value5) + ","
                  + event.orientation.y + "," + event.orientation.z);
  //Serial.println((String) value1);
  //Serial.println((String) value1 + "," + value2 + "," + value3 + "," + value4 + "," + value5);                 //Print value 1
  
  delay(10);                          //Small delay
 
}
