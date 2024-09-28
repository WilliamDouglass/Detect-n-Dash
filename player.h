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
    
    
    
    float size;
    float speed;
    float runSpeed;
    float walkSpeed;
    Color playerCol;
    float camSens;
    
         

public:
    Player(Vector3 startPos, float initSize, float initSpeed, Color initColor);

    void Update();

    void HandleCamera();
    
    void Draw();

    void Move();

    Camera3D getCamera() const;
    int getSize() const;
    Vector3 getPosition() const;
    

};
#endif