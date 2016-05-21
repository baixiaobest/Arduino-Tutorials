
mySnake game(millis());
Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

int command=0;

void drawEverything();
void checkCommunication();

void setup() {
  Serial.begin(9600);
  
  matrix.begin(0x70);  // pass in the address
  matrix.setRotation(3);
  matrix.setBrightness(3);
}
void loop(){
  checkCommunication();
  if(command!=0){
    switch(command){
      case 1:
        game.setDirection(mySnake::UP);
        break;
      case 2:
        game.setDirection(mySnake::RIGHT);
        break;
      case 3:
        game.setDirection(mySnake::DOWN);
        break;
      case 4:
        game.setDirection(mySnake::LEFT);
        break;
    }
    command = 0;
  }
  
  
  
  if(game.getStatus()==mySnake::DIE) game.init(millis(), 1);
  matrix.clear();
  drawEverything();
  matrix.writeDisplay();
  delay(500);
  game.nextStep();
 
}

void drawEverything(){
  std::vector<std::pair<int,int> > snake = game.getSnake();
  std::vector<std::pair<int,int> > goodies = game.getGoodies();
  for(int i=0; i<snake.size(); i++){
    matrix.drawPixel(snake[i].second, snake[i].first, LED_ON);
  }
  for(int i=0; i<goodies.size(); i++){
    matrix.drawPixel(goodies[i].second, goodies[i].first, LED_ON);
  }
}

void checkCommunication(){
  command = (int) Serial.read();
  Serial.flush();
}
