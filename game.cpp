
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
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "game");  

    // Define the camera to look into our 3d world
    // Camera3D camera = { 0 };


    DisableCursor();

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    ScoreTracker sTracker;
    std::vector<Coin> coinList = initCoins(10,sTracker);

    Player mainPlayer (Vector3{0,0,0},1,0.03f,MAROON);


    Detector d1 (Vector2{0.0f,0.0f},2,mainPlayer,5.0f,4.0f,10.0f);

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

        BeginDrawing();

        DrawText(("Score: " + std::to_string(sTracker.getPoint())).c_str(), 5,30,20,WHITE);
            ClearBackground(BLACK);
                
                BeginMode3D(mainPlayer.getCamera());

                Vector2 position = {0,0};

                Vector3 centerPoint = { position.x, 0, position.y }; // Center vertex (bottom)
                Vector3  topLeftPoint = {1,1,1};
                Vector3 topRightPoint = {-1,1,1};

                    // Draw the triangle
                DrawTriangle3D(centerPoint, topRightPoint, topLeftPoint, YELLOW);


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