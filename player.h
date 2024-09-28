#ifndef PlayerH
#define PlayerH

#include <raylib.h>
#include <raymath.h>
#include <rcamera.h>
#include <iostream>

class Player
{
private:
    Vector3 playerPosition;
    float roation;
    Camera3D camera;
    Vector3 cameraOffset;
    Vector2 forward;

   
    
    
    float size;
    float speed;
    float runSpeed;
    float walkSpeed;
    Color playerCol;
    float camSens;

    int maxLives;
    int curLives;
    Vector3 startPos;

    
         

public:
    Player(Vector3 initSartPos, float initSize, float initSpeed, Color initColor);

    void Update();

    void HandleCamera();
    
    void Draw();

    void Move();

    void Dead();

    Camera3D getCamera() const;
    int getSize() const;
    Vector3 getPosition() const;
    int getCurLives()const;
    

};
#endif