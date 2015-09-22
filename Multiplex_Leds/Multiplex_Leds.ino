#include "alphebetMapping.h"
#include <avr/pgmspace.h>

const int x[3] = {10,9,8};
const int y[3] = {5,4,3};
int prevTime, currentTime;
int timeInterval = 1500;
int multiplexInterval = 1;
int alphebetNum = 0;
String incomingString;
int currentMap[3][3] = {{0,0,0},{0,0,0},{0,0,0}};

void setup() {
  pinMode(x[0],OUTPUT);
  pinMode(x[1],OUTPUT);
  pinMode(x[2],OUTPUT);
  pinMode(y[0],OUTPUT);
  pinMode(y[1],OUTPUT);
  pinMode(y[2],OUTPUT);
  digitalWrite(x[0],HIGH);
  digitalWrite(x[1],HIGH);
  digitalWrite(x[2],HIGH);
  digitalWrite(y[0],LOW);
  digitalWrite(y[1],LOW);
  digitalWrite(y[2],LOW);
  Serial.begin(9600);
  prevTime = millis();
  incomingString = "";
}

void loop() {
  currentTime = millis();
  if(currentTime - prevTime > timeInterval){ //check timer for LEDs update
    prevTime = currentTime;
    //turnoff LEDs before displaying new character
    displayBitmap(nullMap);
    delay(10);
    //display new character
    if(incomingString != ""){
      assignMap(currentMap, alphebet[(int)incomingString[0]-97]);
      incomingString = incomingString.substring(1,incomingString.length());
    }else{//display nothing when there is no incoming string
      assignMap(currentMap, nullMap);
    }
  }
  if(Serial.available()){
    incomingString += Serial.readString();
  }
  displayBitmap(currentMap); 
}

void displayBitmap(int Bitmap[][3])
{
  for(int i=0; i<3; i++){
    digitalWrite(y[i],HIGH);
    for(int k=0; k<3; k++){
      if(Bitmap[i][k]==0){
        digitalWrite(x[k], HIGH);
      }else{
        digitalWrite(x[k],LOW);
      } 
    }
    delay(multiplexInterval);
    digitalWrite(y[i],LOW);
  }
}

void assignMap(int me[][3], int other[][3]){
  for(int i=0; i<3; i++){
    for(int k=0; k<3; k++){
      me[i][k] = other[i][k];
    }
  }
}
