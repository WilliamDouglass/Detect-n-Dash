#ifndef CoinH
#define CoinH

#include <raylib.h>
#include "scoreTracker.h"
#include "player.h"
#include <iostream>
#include <raymath.h>


class Coin
{
private:
    /* data */
    Vector3 position;
    float radius;
    Color coinColor;
    bool collected;
    ScoreTracker &st;
    Model model;
    float roation;

    

public:
    Coin(Vector3 aPos, ScoreTracker &aST, Model aModel);
    void Update();

    void Draw();

    void Collect();

    bool checkColission(const Player &playerRef);
    
};
#endif