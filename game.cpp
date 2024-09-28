
#include "raylib.h"
#include "player.h"
#include "coin.h"
#include "scoreTracker.h"
#include <vector>


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



    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

        BeginDrawing();

        DrawText(("Score: " + std::to_string(sTracker.getPoint())).c_str(), 5,30,20,WHITE);
            ClearBackground(BLACK);
                
                BeginMode3D(mainPlayer.getCamera());

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