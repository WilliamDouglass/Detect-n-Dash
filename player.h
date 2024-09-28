#ifndef PlayerH
#define PlayerH

#include <raylib.h>
#include <raymath.h>
#include <rcamera.h>

class Player
{
private:
    Vector3 playerPosition;
    float roation;
    Camera3D camera;
    Vector3 cameraOffset;
    Vector2 forward;
    // float cameraYaw = 0.0f; 
    // float cameraPitch = 0.0f;
    // Rectangle collisionBox;
    
    
    
    int size;
    float speed;
    Color playerCol;
    
         

public:
    Player(Vector3 startPos, int initSize, float initSpeed, Color initColor);

    void Update();

    void HandleCamera();
    
    void Draw();

    void Move();

    Camera3D getCamera() const;
    int getSize() const;
    Vector3 getPosition() const;
    

};
#endif