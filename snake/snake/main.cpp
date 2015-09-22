//
//  main.cpp
//  snake
//
//  Created by Baixiao Huang on 9/20/15.
//  Copyright (c) 2015 Baixiao Huang. All rights reserved.
//

#include <iostream>
#include "mySnake.h"
#include "time.h"
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

void render(mySnake game);
int kbhit();

int main(int argc, const char * argv[]) {
    mySnake game((int)time(NULL),61);
    while (true) {
            
        char c;
        cin >> c;
        switch (c) {
            case 'w':
                game.setDirection(mySnake::UP);
                break;
            case 'd':
                game.setDirection(mySnake::RIGHT);
                break;
            case 's':
                game.setDirection(mySnake::DOWN);
                break;
            case 'a':
                game.setDirection(mySnake::LEFT);
            default:
                break;
        }
        int status = game.nextStep();
    
        switch (status) {
            case mySnake::DIE:
                cout << "Game Over" << endl;
                return 0;
            case mySnake::GET_POINT:
            case mySnake::NOTHING:
                break;
        }
        render(game);
    
    }
}

void render(mySnake game){
    string pic[8]={"00000000",
                   "00000000",
                   "00000000",
                   "00000000",
                   "00000000",
                   "00000000",
                   "00000000",
                   "00000000",};
    vector<pair<int, int>> snake = game.getSnake();
    vector<pair<int,int>> goodies = game.getGoodies();
    for (int i=0; i<snake.size(); i++) {
        pic[7-snake[i].second][snake[i].first]='S';
    }
    for (int i=0; i<goodies.size(); i++) {
        pic[7-goodies[i].second][goodies[i].first]='G';
    }
    for (int i=0; i<8; i++) {
        cout << pic[i] << endl;
    }
}

int kbhit(void)
{
    struct termios oldt, newt;
    int ch;
    int oldf;
    
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    
    ch = getchar();
    
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    
    if(ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }
    
    return 0;
}
