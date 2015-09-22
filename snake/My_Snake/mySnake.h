//
//  mySnake.h
//  snake
//
//  Created by Baixiao Huang on 9/20/15.
//  Copyright (c) 2015 Baixiao Huang. All rights reserved.
//

#ifndef snake_mySnake_h
#define snake_mySnake_h

#include <vector>
#include <stdlib.h>

class mySnake
{
public:
    enum Direction{UP, RIGHT, DOWN, LEFT};
    enum Status{NOTHING, GET_POINT, DIE};
    
    mySnake(unsigned int seed=0, int numOfGo=1){
        point = 0;
        bonus = 10;
        mySeed = seed;
        srand(mySeed);
        snake.push_back(std::pair<int,int>(1,2));
        snake.push_back(std::pair<int,int>(2,2));
        numOfGoodies = numOfGo;
        initializeGoodies();
        status = mySnake::NOTHING;
        direction = RIGHT;
    };
    int nextStep();
    
    void setNumOfGoodies(int num){numOfGoodies = num;};
    void setBonus(int bo){bonus = bo;};
    bool setDirection(int dir);
    
    int getPoint(){return point;};
    int getStatus(){return status;};
    int getCurrentNumOfGoodies(){return (int) goodies.size();};
    std::vector<std::pair<int,int> > getGoodies(){return goodies;};
    std::vector<std::pair<int,int> > getSnake(){return snake;};
private:
    void initializeGoodies();
    void addGoodie();
    void moveSnake();
    
    
    std::vector<std::pair<int, int> > goodies;
    std::vector<std::pair<int, int> > snake;
    int point;
    int direction;
    int numOfGoodies;
    int status;
    unsigned int mySeed;
    int bonus;
};

/*Move the snake, check if it eats goodie, add points.
 If snake hit the wall or itself, it dies*/
int mySnake::nextStep()
{
    int snakeX = snake[snake.size()-1].first;
    int snakeY = snake[snake.size()-1].second;
    
    //snake moves out of bound
    if ((direction==UP && snakeY==7)
        || (direction==RIGHT && snakeX==7)
        || (direction==DOWN && snakeY==0)
        || (direction==LEFT && snakeX==0)) {
        status = DIE;
        return status;
    }
    //snakes eat a goodie
    for (int i=0; i<goodies.size(); i++) {
        int gx = goodies[i].first;
        int gy = goodies[i].second;
        if ((direction == UP && snakeX==gx && snakeY==gy-1)
            || (direction == RIGHT && snakeX==gx-1 && snakeY==gy)
            || (direction == DOWN && snakeX==gx && snakeY==gy+1)
            || (direction == LEFT && snakeX==gx+1 && snakeY == gy)) {
            point += bonus;
            status = GET_POINT;
            snake.push_back(std::pair<int, int>(gx, gy));
            goodies.erase(goodies.begin()+i);
            initializeGoodies();
            return status;
        }
    }
    
    moveSnake();
    
    //snakes bites itself
    for (int i=0; i<snake.size()-1; i++) {
        if (snake[snake.size()-1].first == snake[i].first
            && snake[snake.size()-1].second == snake[i].second) {
            status = DIE;
            return status;
        }
    }
    
    status = NOTHING;
    return status;
}

void mySnake::moveSnake(){
    int x(0), y(0);
    switch (direction) {
        case UP:
            y=1;
            break;
        case RIGHT:
            x=1;
            break;
        case DOWN:
            y=-1;
            break;
        case LEFT:
            x=-1;
            break;
    }
    snake.push_back(std::pair<int, int>(snake[snake.size()-1].first+x, snake[snake.size()-1].second+y));
    snake.erase(snake.begin());
}


void mySnake::initializeGoodies()
{
    //nowhere to place new goodie
    if (goodies.size()+snake.size() == 64) {
        return;
    }
    //add goodies until num of goodies reach specified limit
    while (goodies.size() <numOfGoodies) {
        addGoodie();
    }
}

void mySnake::addGoodie()
{
    int x,y;
    bool flag = false;
    while (flag==false) {
        x = rand() % 8;
        y = rand() % 8;
        flag = true;
        for (int i=0; i<snake.size(); i++) {
            if (snake[i].first==x
                && snake[i].second==y) {
                flag = false;
            }
        }
        for (int i=0; i<goodies.size(); i++) {
            if (goodies[i].first==x
                && goodies[i].second==y) {
                flag = false;
            }
        }
    }
    goodies.push_back(std::pair<int, int>(x,y));
}

bool mySnake::setDirection(int dir){
    switch (dir) {
        case UP:
            if (direction==DOWN) {
                return false;
            }
            break;
        case RIGHT:
            if (direction==LEFT) {
                return false;
            }
            break;
        case DOWN:
            if (direction==UP) {
                return false;
            }
            break;
        case LEFT:
            if (direction==RIGHT) {
                return false;
            }
            break;
        default:
            break;
    }
    direction = dir;
    return true;
}

#endif

