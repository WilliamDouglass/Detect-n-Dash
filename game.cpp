
#include "raylib.h"
#include "player.h"
#include "coin.h"
#include "scoreTracker.h"
#include <vector>
#include "detector.h"




std::vector<Coin> initCoins(int numCoins, ScoreTracker& st){
    
    std::vector<Coin> coinList;

    
    for (int i = 0; i < numCoins; i++)
    {
        coinList.emplace_back(Vector3{(float)GetRandomValue(-10,10),0,(float)GetRandomValue(-10,10)},st);
    }
    return coinList;
}



int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1000;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "game");  

    // Define the camera to look into our 3d world
    // Camera3D camera = { 0 };


    DisableCursor();

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    ScoreTracker sTracker;
    std::vector<Coin> coinList = initCoins(10,sTracker);

    Player mainPlayer (Vector3{0,0,0},0.7f,0.03f,Color{0,60,255,255});
    
    std::vector<Vector3> d1PotralPoints;
    d1PotralPoints.push_back(Vector3{15,0,5});
    d1PotralPoints.push_back(Vector3{6,0,-9});
    d1PotralPoints.push_back(Vector3{-3,0,10});




    Detector d1 (Vector3Zero(),0,mainPlayer,5,8,45,d1PotralPoints,2);



    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {   

        if(IsKeyPressed(KEY_P))
        {
            mainPlayer.Dead();
        }

        BeginDrawing();

        DrawText(("Score: " + std::to_string(sTracker.getPoint())).c_str(), 5,30,20,WHITE);
            ClearBackground(BLACK);

                
                BeginMode3D(mainPlayer.getCamera());

                DrawCube(Vector3{3,0,0},1,1,1,GREEN);

                d1.Update();



                for (Coin& aCoin : coinList)
                {
                    aCoin.checkColission(mainPlayer);
                    aCoin.Update();
                }
                            
                mainPlayer.Update();
                


                DrawGrid(50, 1.0f);
                
                EndMode3D();

            DrawFPS(10, 10);

        EndDrawing();
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}