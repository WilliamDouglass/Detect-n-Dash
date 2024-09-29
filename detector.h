#ifndef detectorH
#define detectorH
#include <raylib.h>
#include "player.h"
#include <cmath>
#include <vector>


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

    //Movement
    int potralIndex;
    std::vector<Vector3> potralPoints;
    float potralSpeed;
    Vector3 startPos;

    //DEBUG
    bool showDebugPoints;




// Function to calculate the triangle vertices based on the position, rotation, and distance
    void GetTriangleVertices(Vector3 position, float rotation, float angle, float distance, Vector3* vertices) ;

    void Draw3DTriangle(Vector3 position, float rotation, float angle, float distance, Color aColor);
    void Draw();
    void Collision();
    void Potral();
    void DebugDrawPotralPoints();
    int getNextIndex();
    
    public:
    Detector(float initRotation, Player &initPlayerRef,float initvDebth,
    float initvWidth,float initvAngle,std::vector<Vector3> initPotralPoints, float initpSpeed);

    void Update();




};


#endif