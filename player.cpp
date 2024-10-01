#include "player.h"

     
Player::Player(Vector3 initSartPos, float initSize, float initSpeed,Model model,ScoreTracker &sTracker)
    :startPos(initSartPos),size(initSize),runSpeed(initSpeed),playerModel(model), tracker(sTracker){
        roation = 0;
        cameraOffset = (Vector3){0.0f, 4.0f, -8.0f};
        camera.position = Vector3Add(startPos,cameraOffset);  // Camera position
        camera.target = (Vector3){ 0.0f, 1.0f, 0.0f };      // Camera looking at point
        camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
        camera.fovy = 45.0f;                                // Camera field-of-view Y
        camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type
        walkSpeed = runSpeed/2;
        speed = runSpeed;
        camSens = 0.0015f;
        playerPosition = startPos;
        maxLives = 3;
        curLives = maxLives;
        playerDead = false;
        iFrams = 2; // 2 sec of I frames
        timmer = 0;
    }

void Player::Update(){
    if(!(timmer >= iFrams)){
        timmer += GetFrameTime();
    }
    HandleCamera();
    Move();
    Draw();
}

void Player::HandleCamera(){
    Vector2 mousePositionDelta = GetMouseDelta();
    CameraYaw(&camera, -mousePositionDelta.x*camSens, true);
    camera.position.y = playerPosition.y + cameraOffset.y;

    forward = {
        playerPosition.x - camera.position.x,
        playerPosition.z - camera.position.z
    };
    Vector2Normalize(forward);
    camera.target = Vector3{playerPosition.x,playerPosition.y + 1, playerPosition.z};

}

void Player::Draw(){
    Color playerCol = WHITE;
    if(iFrams >= timmer)
    {
        playerCol.a = 50;
    }else{
        playerCol.a = 255;
    }

    // DrawCylinder(playerPosition,size,size,size,20,playerCol);
    roation = atan2(forward.y,forward.x) * (180.0f/PI) * -1;
    roation += 90;
    
    //Ghost bobbing
    float pos = playerPosition.y;
    pos =sin(tracker.getTimmer()*3);
    std::cout << "Y Position: " << pos << std::endl;
    playerPosition.y += pos/90;

    DrawModelEx(playerModel,playerPosition,Vector3{0,1,0},roation,Vector3One(),playerCol);
}    

void Player::Dead(bool force){
    if (force)
    {
        curLives = 0;
    }
    
    if(iFrams >= timmer){return;} // in i frames
    //reset position
    playerPosition = startPos;
    curLives--;
    timmer = 0;

    //res camea
    camera.position = Vector3Add(playerPosition,cameraOffset);  // Camera position
    camera.target = (Vector3){ 0.0f, 1.0f, 0.0f };      // Camera looking at point
    
    if(curLives <= 0){
        std::cout << "[PlayerDead]" << std::endl;
        playerDead = true;
    }
}

void Player::Move(){ //TODO FIX
    // const char* str = TextFormat("Forward ")

// std::cout 
//           << " POS: (" << playerPosition.x << ", " 
//           << playerPosition.y << ", " 
//           << playerPosition.z << ")" << std::endl;

    Vector3 newPlayerPos = playerPosition;
    Vector3 newCamPos = camera.position;

    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
    {   
        newPlayerPos.x += forward.x * speed;
        newPlayerPos.z += forward.y * speed;
        newCamPos.x += forward.x * speed;
        newCamPos.z += forward.y * speed;
    }

    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) 
    {
        newPlayerPos.x -= forward.x * speed;
        newPlayerPos.z -= forward.y * speed;
        newCamPos.x -= forward.x * speed;
        newCamPos.z -= forward.y * speed;
    }
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
    {
        newPlayerPos.x += forward.y * speed;
        newPlayerPos.z -= forward.x * speed;
        newCamPos.x += forward.y * speed;
        newCamPos.z -= forward.x * speed;
    }
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
    {
        newPlayerPos.x -= forward.y * speed;
        newPlayerPos.z += forward.x * speed;
        newCamPos.x -= forward.y * speed;
        newCamPos.z += forward.x * speed;
    }

    // For x-axis: Check if the player is within the range [-35, 35]
    if(newPlayerPos.x >= -35.0f && newPlayerPos.x <= 35.0f) {
        playerPosition.x = newPlayerPos.x;
        camera.position.x = newCamPos.x;
    }

    // For z-axis: Check if the player is within the range [-35, 35]
    if(newPlayerPos.z >= -35.0f && newPlayerPos.z <= 35.0f) {
        playerPosition.z = newPlayerPos.z;
        camera.position.z = newCamPos.z;
    }


}


void Player::Reset()
{   
    timmer = 0;

    //alive 
    playerDead = false;
    //position
    playerPosition = startPos;
    //camera
    camera.position = Vector3Add(playerPosition,cameraOffset);  // Camera position
    camera.target = (Vector3){ 0.0f, 1.0f, 0.0f };      // Camera looking at point
    
    //lives
    curLives = maxLives;
}


Camera3D Player::getCamera() const {return camera;}
int Player::getSize() const {return size;}
Vector3 Player::getPosition() const{return playerPosition;}
int Player::getCurLives()const{return curLives;}
bool Player::isDead()const{return playerDead;}

bool Player::isInIFrames()const{return (iFrams >= timmer);}
