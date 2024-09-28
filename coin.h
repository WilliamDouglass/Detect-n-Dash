#ifndef CoinH
#define CoinH

#include <raylib.h>
#include "scoreTracker.h"
#include "player.h"
#include <iostream>


class Coin
{
private:
    /* data */
    Vector3 position;
    float radius;
    Color coinColor;
    bool collected;
    ScoreTracker &st;
    

public:
    Coin(Vector3 aPos, ScoreTracker &aST);
    void Update();

    void Draw();

    void Collect();

    bool checkColission(const Player &playerRef);
    
};
#endif