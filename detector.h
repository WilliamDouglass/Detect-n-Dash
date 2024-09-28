#ifndef detectorH
#define detectorH
#include <raylib.h>
#include "player.h"
#include <cmath>


class Detector{
    private:
    Vector3 position;
    float roationYaw;
    Player &playerRef;
    float visionDebth;
    float visionWidth;
    float visionAngle;
    Color coneColor;
    Color detectColor;
    Color defaultColor;
    float bodyRadius;
    float bodyHight;
    Color bodyColor;

// Function to calculate the triangle vertices based on the position, rotation, and distance
    void GetTriangleVertices(Vector3 position, float rotation, float angle, float distance, Vector3* vertices) ;

    void Draw3DTriangle(Vector3 position, float rotation, float angle, float distance, Color aColor);
    void Draw();
    void Collision();
    
    public:
    Detector(Vector3 initPos, float initRotation, Player &initPlayerRef,float initvDebth,
    float initvWidth,float initvAngle, float initRadius, float initHight,Color initBodyColor);

    void Update();


};


#endif