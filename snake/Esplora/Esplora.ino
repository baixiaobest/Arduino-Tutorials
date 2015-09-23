#include <Esplora.h>

int lastCommand=0;
int command=0;

void setup() {
  Serial1.begin(9600);
}

void loop() {
  if(Esplora.readButton(SWITCH_UP)==LOW){
    command=1;
  }else if(Esplora.readButton(SWITCH_RIGHT)==LOW){
    command=2;
  }else if(Esplora.readButton(SWITCH_DOWN)==LOW){
    command=3;
  }else if(Esplora.readButton(SWITCH_LEFT)==LOW){
    command=4;
  }
  if(command!=0 && lastCommand != command){
    Serial1.write(command);
    lastCommand = command;
  }
}
