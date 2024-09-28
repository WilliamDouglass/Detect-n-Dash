#include <raylib.h>
#include "player.h"


Vector3 position;
float roation;

int size;
int speed;
Color playerCol;

     
Player::Player(Vector3 startPos, int initSize, int initSpeed, Color initColor)
    :position(startPos),size(initSize),speed(initSpeed),playerCol(initColor){
        roation = 0;
    }
    
void Player::Draw(){
    DrawCube(position,size,size,size,playerCol);
}    
    

