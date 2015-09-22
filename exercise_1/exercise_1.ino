int redLed = 3;
int greenLed = 5;
int blueLed = 6;

void setup() {
  pinMode(redLed,OUTPUT );
  pinMode(greenLed,OUTPUT );
  pinMode(blueLed,OUTPUT );
}

void loop() {

  analogWrite ( greenLed, 0);
  analogWrite ( redLed, 0);
  analogWrite ( blueLed, 0);
  
}
