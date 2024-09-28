#include "player.h"

     
Player::Player(Vector3 startPos, int initSize, float initSpeed, Color initColor)
    :playerPosition(startPos),size(initSize),speed(initSpeed),playerCol(initColor){
        roation = 0;
        cameraOffset = (Vector3){0.0f, 4.0f, -8.0f};
        camera.position = Vector3Add(playerPosition,cameraOffset);  // Camera position
        camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
        camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
        camera.fovy = 45.0f;                                // Camera field-of-view Y
        camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type
    

    }

void Player::Update(){
    HandleCamera();
    Move();
    Draw();
}

void Player::HandleCamera(){
    Vector2 mousePositionDelta = GetMouseDelta();
    CameraYaw(&camera, -mousePositionDelta.x*0.003f, true);
    camera.position.y = playerPosition.y + cameraOffset.y;

    forward = {
        playerPosition.x - camera.position.x,
        playerPosition.z - camera.position.z
    };
    Vector2Normalize(forward);
    camera.target = Vector3{playerPosition.x,playerPosition.y + 1, playerPosition.z};

}



void Player::Draw(){
    // DrawCube(playerPosition,size,size,size,playerCol);
    DrawCylinder(playerPosition,size,size,size,20,playerCol);
}    


void Player::Move(){
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) // forward
    {
        playerPosition.x += forward.x * speed;
        playerPosition.z += forward.y * speed;
        camera.position.x += forward.x * speed;
        camera.position.z += forward.y * speed;
    }
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) // forward
    {
        playerPosition.x -= forward.x * speed;
        playerPosition.z -= forward.y * speed;
        camera.position.x -= forward.x * speed;
        camera.position.z -= forward.y * speed;
    }
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
    {
        playerPosition.x += forward.y * speed;
        playerPosition.z -= forward.x * speed;
        camera.position.x += forward.y * speed;
        camera.position.z -= forward.x * speed;
    }
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
    {
        playerPosition.x -= forward.y * speed;
        playerPosition.z += forward.x * speed;
        camera.position.x -= forward.y * speed;
        camera.position.z += forward.x * speed;
    }
    
}

Camera3D Player::getCamera() const {return camera;}
    

