#ifndef PlayerH
#define PlayerH

#include <raylib.h>

class Player
{
private:
    Vector3 position;
    float roation;
    
    int size;
    int speed;
    Color playerCol;
    
         

public:
    Player(Vector3 startPos, int initSize, int initSpeed, Color initColor);

    void Draw();
    

};

#endif

