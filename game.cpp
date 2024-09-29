
#include "raylib.h"
#include "player.h"
#include "coin.h"
#include "scoreTracker.h"
#include <vector>
#include "detector.h"
#include <iostream>
#include <string>





std::vector<Coin> initCoins(int numCoins, ScoreTracker& st){
    
    std::vector<Coin> coinList;

    
    for (int i = 0; i < numCoins; i++)
    {
        coinList.emplace_back(Vector3{(float)GetRandomValue(-10,10),0,(float)GetRandomValue(-10,10)},st);
    }
    return coinList;
}

enum MenuPages{
    MainPage,
    GamePage,
    ScorePage
};

void MainMenu(MenuPages &curPage,Rectangle playButton, Rectangle quitButton, bool &closeWin){
    if (IsCursorHidden())
    {
        EnableCursor();
    }
    Vector2 mousePos = GetMousePosition();
    bool playHover = CheckCollisionPointRec(mousePos,playButton);
    bool quitHover = CheckCollisionPointRec(mousePos,quitButton);

    if (playHover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        curPage = GamePage;
    }
    if (quitHover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {   
        //TODO
        // closeWin = true;
        // return;
    }
    


    BeginDrawing();
    ClearBackground(LIGHTGRAY);
    int hoverAlpha = 150;

    if(playHover){
        DrawRectangleRec(playButton,Color{70,157,255,static_cast<unsigned char>(hoverAlpha)});
    }else{
        DrawRectangleRec(playButton,Color{70,157,255,200});
    }
    if(quitHover){
        DrawRectangleRec(quitButton,Color{70,157,255,static_cast<unsigned char>(hoverAlpha)});
    }else{
        DrawRectangleRec(quitButton,Color{70,157,255,200});
    }

    DrawText("Play",playButton.x + 130,playButton.y+5,40,DARKGRAY);
    DrawText("Quit",quitButton.x + 135,quitButton.y+5,40,DARKGRAY);
    EndDrawing();
}

void Gameplay(Player &mainPlayer,ScoreTracker &sTracker, std::vector<Coin> &coinList, Detector &d1)
{   
    if (!IsCursorHidden())
    {
        DisableCursor();
    }

    if (mainPlayer.isDead())
    {
        //Reset
    }
        BeginDrawing();
        DrawText(("Score: " + std::to_string(sTracker.getPoint())).c_str(), 5,30,20,WHITE);
        DrawText(("Lives: " + std::to_string(mainPlayer.getCurLives())).c_str(), 5,50,20,WHITE);

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

void ScoreMenu(Player &mainPlayer,ScoreTracker &sTracker,Rectangle continueButton,MenuPages &curPage){
    if (IsCursorHidden())
    {
        EnableCursor();
    }
    
    int points = sTracker.getPoint();
    Vector2 mousePos = GetMousePosition();
    bool continueHover = CheckCollisionPointRec(mousePos,continueButton);

    if (continueHover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {   
        curPage = GamePage;
    }


    BeginDrawing();
    ClearBackground(LIGHTGRAY);
    
    int hoverAlpha = 150;

    if(continueHover){
        DrawRectangleRec(continueButton,Color{70,157,255,static_cast<unsigned char>(hoverAlpha)});
    }else{
        DrawRectangleRec(continueButton,Color{70,157,255,200});
    }

    DrawText("Continue?",continueButton.x + 70,continueButton.y+5,40,DARKGRAY);


    std::string scoreText = "Score: " + std::to_string(sTracker.getPoint());
    DrawText(scoreText.c_str(), 10 , GetScreenHeight() - 50, 40, DARKGRAY);
    
    EndDrawing();
}



int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1000;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "game");
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second


    //MainMenu
    float buttonWidth = 350;
    float buttonHight = 50;
    Rectangle playButton = {screenWidth/2 - buttonWidth/2, screenHeight/2 + 30,buttonWidth,buttonHight};
    Rectangle quitButton = {screenWidth/2 - buttonWidth/2, screenHeight/2 + 100,buttonWidth,buttonHight};
    MenuPages curPage = ScorePage;
    bool closeWindow = false;


    //---------------------------------------------------------------------------------------
    //Game init


    ScoreTracker sTracker;
    std::vector<Coin> coinList = initCoins(10,sTracker);

    Player mainPlayer (Vector3{0,0,0},0.7f,0.03f,Color{0,60,255,255});
    
    std::vector<Vector3> d1PotralPoints;
    d1PotralPoints.push_back(Vector3{15,0,5});
    d1PotralPoints.push_back(Vector3{6,0,-9});
    d1PotralPoints.push_back(Vector3{-3,0,10});

    Detector d1 (Vector3Zero(),0,mainPlayer,5,8,45,d1PotralPoints,2);

    //---------------------------------------------------------------------------------------


    // Main game loop
    while (!WindowShouldClose() || closeWindow)    // Detect window close button or ESC key
    {   
        if(curPage == MainPage){
            MainMenu(curPage,playButton,quitButton,closeWindow);
        }

        if(curPage== GamePage){
            Gameplay(mainPlayer,sTracker,coinList,d1);
            if(mainPlayer.isDead())
            {
                curPage = ScorePage;
            }
        }

        if(curPage == ScorePage){
            ScoreMenu(mainPlayer,sTracker,playButton,curPage);
        }
    }





    CloseWindow();       

    return 0;
}