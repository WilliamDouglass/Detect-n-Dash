#include "detector.h"

Detector::Detector(Vector3 initPos, float initRotation, Player &initPlayerRef,float initvDebth,
    float initvWidth,float initvAngle,std::vector<Vector3> initPotralPoints, float initpSpeed)
    :position(initPos),roationYaw(initRotation),playerRef(initPlayerRef),visionDebth(initvDebth),
    visionWidth(initvWidth),visionAngle(initvAngle),potralPoints(initPotralPoints),potralSpeed(initpSpeed){
        defaultColor = Color{255,255,156,255}; //light yellow Color{255,255,156}
        detectColor = Color{255,77,0,255}; //Redish orange Color{255,77,0}
        coneColor = defaultColor;
        potralIndex = 0;
        bodyRadius =0.8f;
        bodyHight = 1;
        bodyColor = RED;
        showDebugPoints = true;


    }

void Detector::Update(){
    Draw();
    Collision();
    Potral();
    DebugDrawPotralPoints();
}

void Detector::Potral(){
    Vector3 directToPoint = Vector3Subtract(potralPoints[potralIndex], position);
    directToPoint = Vector3Normalize(directToPoint);
    float stepSize = potralSpeed/30;
    position = Vector3 { position.x + directToPoint.x * stepSize,
                 position.y + directToPoint.y * stepSize,
                 position.z + directToPoint.z * stepSize };

    //Update Angle    
    float angleRadians = atan2(potralPoints[potralIndex].z - position.z, potralPoints[potralIndex].x - position.x);
    
    roationYaw = (angleRadians * (180.0f / PI)) - 180;

    if(Vector3DotProduct(directToPoint,potralPoints[potralIndex]) < 0)
    {
        potralIndex = getNextIndex();
    }


}

void Detector::DebugDrawPotralPoints(){
    if(!showDebugPoints){return;}

    for(Vector3 vet3 : potralPoints)
    {
        DrawSphere(vet3,0.2f,PINK);
    }


}


void Detector::Draw(){
    Draw3DTriangle(position,roationYaw,visionAngle,visionDebth,coneColor);
    DrawCylinder(position,bodyRadius/1.5,bodyRadius,bodyHight,20,bodyColor);
}

void Detector::Collision(){
    Vector3 playerPosition = playerRef.getPosition();
    Vector3 triBounds[3];
    GetTriangleVertices(position,roationYaw,visionAngle,visionDebth, triBounds);
    Vector2 p1 = Vector2{triBounds[0].x,triBounds[0].z};
    Vector2 p2 = Vector2{triBounds[1].x,triBounds[1].z};
    Vector2 p3 = Vector2{triBounds[2].x,triBounds[2].z};

    bool collision = CheckCollisionPointTriangle(Vector2{playerPosition.x,playerPosition.z},p1,p2,p3);
    

    if (collision)
    {
        coneColor = detectColor;
        playerRef.Dead();
    }else{
        coneColor = defaultColor;
    }

}

void Detector::Draw3DTriangle(Vector3 position, float rotation, float angle, float distance, Color aColor) {
    Vector3 vertices[3];
    GetTriangleVertices(position, rotation, angle, distance, vertices);

    // DrawSphere(vertices[0],0.3f,BLUE);
    // DrawSphere(vertices[1],0.3f,RED);
    // DrawSphere(vertices[2],0.3f,PINK);

    // Draw the triangle
    DrawTriangle3D(vertices[1], vertices[0], vertices[2], aColor);
}

// Function to calculate the triangle vertices based on the position, rotation, angle, and distance
void Detector::GetTriangleVertices(Vector3 position, float rotation, float angle, float distance, Vector3* vertices) {
    // Calculate the base distance (how far the base vertices are from the tip)
    float baseHalf = distance * tan(angle * (PI / 180.0f) / 2); // Half the base width of the triangle

    // First vertex is the tip of the triangle (position)
    vertices[0] = position;

    // Calculate the direction vector based on the rotation (for the tip to base direction)
    float rotRadians = rotation * (PI / 180.0f);
    Vector3 direction = { cos(rotRadians), 0.0f, sin(rotRadians) };

    // Calculate the midpoint of the base by moving 'distance' units back from the tip
    Vector3 baseMidpoint = {
        position.x - distance * direction.x,
        position.y,
        position.z - distance * direction.z
    };

    // Now calculate the two base vertices by adding and subtracting half the base width
    Vector3 perpendicular = { -direction.z, 0.0f, direction.x }; // Perpendicular vector to direction

    vertices[1] = (Vector3) {
        baseMidpoint.x + baseHalf * perpendicular.x,
        baseMidpoint.y,
        baseMidpoint.z + baseHalf * perpendicular.z
    };

    vertices[2] = (Vector3) {
        baseMidpoint.x - baseHalf * perpendicular.x,
        baseMidpoint.y,
        baseMidpoint.z - baseHalf * perpendicular.z
    };
}

int Detector::getNextIndex(){
    if(potralIndex >= potralPoints.size()-1){
        return 0;
    }else{
        return potralIndex+1;
    }
}