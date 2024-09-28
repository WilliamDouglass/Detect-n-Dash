
#include "raylib.h"
#include "player.h"

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

    Player mainPlayer (Vector3{0,0,0},1,0.03f,MAROON);


    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

        BeginDrawing();

            ClearBackground(BLACK);
                BeginMode3D(mainPlayer.getCamera());

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