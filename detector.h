#ifndef detectorH
#define detectorH
#include <raylib.h>
#include "player.h"

class Detector{
    private:
    Vector2 position;
    float roationYaw;
    Player &playerRef;
    float visionDebth;
    float visionWidth;
    float visionAngle;

    public:
    Detector(Vector2 initPos, float initRotation, Player &initPlayerRef,float initvDebth, float initvWidth,float initvAngle);

    void Update();

    void Draw();
};


#endif