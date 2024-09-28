#include "detector.h"

    Detector::Detector(Vector2 initPos, float initRotation, Player &initPlayerRef,float initvDebth, float initvWidth,float initvAngle)
        :position(initPos),roationYaw(initRotation),playerRef(initPlayerRef),visionDebth(initvDebth),visionWidth(initvWidth),visionAngle(initvAngle){}

    void Detector::Update(){
        Draw();
    }

    void Detector::Draw(){
            Vector3 centerPoint = { position.x, 0.0f, position.y }; // Center vertex (bottom)
            Vector3 topRightPoint = {1,0,1};
            Vector3 topLeftPoint = {-1,0,1};

                // Draw the triangle
            DrawTriangle3D(centerPoint, topRightPoint, topLeftPoint, YELLOW);
    }
