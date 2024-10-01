#ifndef PlayerH
#define PlayerH

#include <raylib.h>
#include <raymath.h>
#include <rcamera.h>
#include <iostream>
#include "scoreTracker.h"

class Player
{
private:
    Vector3 playerPosition;
    Vector3 startPos;
    float size;
    float roation;
    Camera3D camera;
    Vector3 cameraOffset;
    Vector2 forward;
    enum MenuPages{
        MainPage,
        GamePage,
        ScorePage
    };
    Model playerModel;

   
    
    
    
    float speed;
    float runSpeed;
    float walkSpeed;
    float camSens;

    int maxLives;
    int curLives;
    
    bool playerDead;

    float timmer;
    float iFrams;

    ScoreTracker &tracker;
         

public:
    
    Player(Vector3 initSartPos, float initSize, float initSpeed, Model model,ScoreTracker &tracker);

    void Update();

    void HandleCamera();
    
    void Draw();

    void Move();

    void Dead(bool force);

    void Reset();

    Camera3D getCamera() const;
    int getSize() const;
    Vector3 getPosition() const;
    int getCurLives()const;
    bool isDead()const;

    bool isInIFrames() const;
    

};
#endif