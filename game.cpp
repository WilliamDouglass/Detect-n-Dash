
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
    int range = 25;

    
    for (int i = 0; i < numCoins; i++)
    {
        coinList.emplace_back(Vector3{(float)GetRandomValue(-range,range),0,(float)GetRandomValue(-range,range)},st);
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
        closeWin = true;
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

void Gameplay(Player &mainPlayer,ScoreTracker &sTracker, std::vector<Coin> &coinList, std::vector<Detector> &dList, int maxCoins)
{   
    if (!IsCursorHidden())
    {
        DisableCursor();
    }

    sTracker.UpdateTimmer();

        BeginDrawing();
        DrawText(("Score: " + std::to_string(sTracker.getPoint())).c_str(), 5,30,20,WHITE);
        DrawText(("Lives: " + std::to_string(mainPlayer.getCurLives())).c_str(), 5,50,20,WHITE);
        const char* text = TextFormat("%.1f", sTracker.getTimmer());
        int textWidth = MeasureText(text, 20);
        DrawText(text, (GetScreenWidth() - textWidth) / 2, 20, 20, MAROON); // Draw text

            ClearBackground(BLACK);

                
                BeginMode3D(mainPlayer.getCamera());
                DrawCylinder(Vector3Zero(),1.5,1.5,-0.3,20,Color{70,157,255,255});

                if (sTracker.getTimmer() < 0 || sTracker.getPoint() >= maxCoins)
                {
                    mainPlayer.Dead(true);
                    sTracker.setTimmerStop(true);
                }
                

                for (Detector& dect : dList)
                {
                    dect.Update();
                }
                

                for (Coin& aCoin : coinList)
                {
                    aCoin.checkColission(mainPlayer);
                    aCoin.Update();
                }
                            
                mainPlayer.Update();
                

                DrawGrid(80, 1.0f);
                
                EndMode3D();

            DrawFPS(10, 10);
        EndDrawing();

}

float getRandFloat(float min, float max, bool onlyPositive) {
    // Generate a random float between min and max
    float randomValue = (min + (static_cast<float>(GetRandomValue(0, 10000)) / 10000.0f) * (max - min));
    
    // Decide randomly to make it positive or negative
    int sign = 1;
    if (!onlyPositive)
    {
        sign = GetRandomValue(0, 1) == 0 ? -1 : 1;
    }
    
    return randomValue * sign; // Return the random float with the appropriate sign
}

Vector3 getRandV3(int min, int max){
    return Vector3{
        getRandFloat(min,max,false),
        0.0f,
        getRandFloat(min,max,false)
    };
}


void initDetector(std::vector<Detector> &dList,Player &mainPlayer)
{
    int numMinDect = 6;
    int numMaxDect = 10;
    // Initialize the Detector objects
    for (int i = 0; i < GetRandomValue(numMinDect,numMaxDect); ++i) {
        // You can modify the initPos or other parameters based on `i` if needed
        std::vector<Vector3> initPotralPoints;
        for(int p = 0; p < GetRandomValue(3,6);p++){ //Rand number of points
            initPotralPoints.push_back(getRandV3(4.0f,30.0f)); // Position of the points
        }

//Refrance for Below
//float initRotation, Player &initPlayerRef,float initvDebth,
//float initvWidth,float initvAngle,std::vector<Vector3> initPotralPoints, float initpSpeed
        Detector newDetector(
            0, mainPlayer, GetRandomValue(4,7),
             GetRandomValue(4,6), GetRandomValue(50,100), initPotralPoints, getRandFloat(4,8,true));
        dList.push_back(newDetector); // Add the new Detector to the vector
    }
}

void ResetGame(Player &mainPlayer, ScoreTracker &sTracker,std::vector<Coin> &coinList,int numCoins,std::vector<Detector> &dList){
    //res player
    mainPlayer.Reset();
    coinList = initCoins(numCoins,sTracker);
    sTracker.reset();
    dList.clear();
    initDetector(dList,mainPlayer);

}

void ScoreMenu(Player &mainPlayer,ScoreTracker &sTracker,Rectangle resetButton, Rectangle quitButton,MenuPages &curPage,bool &closeWin,std::vector<Coin> &coinList,int numCoins,std::vector<Detector> &dList){
    if (IsCursorHidden())
    {
        EnableCursor();
    }
    
    Vector2 mousePos = GetMousePosition();
    bool resetHover = CheckCollisionPointRec(mousePos,resetButton);
    bool quitHover = CheckCollisionPointRec(mousePos,quitButton);


    if (resetHover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {   
        curPage = GamePage;
        ResetGame(mainPlayer,sTracker,coinList,numCoins, dList);

    }
    if (quitHover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {   
        //TODO
        closeWin = true;
    }


    BeginDrawing();
    ClearBackground(LIGHTGRAY);
    
    int hoverAlpha = 150;

    if(resetHover){
        DrawRectangleRec(resetButton,Color{70,157,255,static_cast<unsigned char>(hoverAlpha)});
    }else{
        DrawRectangleRec(resetButton,Color{70,157,255,200});
    }
    if(quitHover){
        DrawRectangleRec(quitButton,Color{70,157,255,static_cast<unsigned char>(hoverAlpha)});
    }else{
        DrawRectangleRec(quitButton,Color{70,157,255,200});
    }

    DrawText("Reset?",resetButton.x + 100,resetButton.y+5,40,DARKGRAY);


    std::string scoreText = "Score: " + std::to_string(sTracker.getPoint());
    DrawText(scoreText.c_str(), 10 , GetScreenHeight() - 50, 40, DARKGRAY);

    const char* timeString = TextFormat("Timer Remaining: %.2f", sTracker.getTimmer());
    DrawText(timeString, 10 , GetScreenHeight() - 100, 40, DARKGRAY);
    
    DrawText("Quit",quitButton.x + 135,quitButton.y+5,40,DARKGRAY);

    
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
    MenuPages curPage = MainPage;
    bool closeWindow = false;


    //---------------------------------------------------------------------------------------
    //Game init

    float timeLimit = 1.5*60; //in seconds
    ScoreTracker sTracker(timeLimit);
    int numCoins = 30;
    std::vector<Coin> coinList = initCoins(numCoins,sTracker);

    Player mainPlayer (Vector3{0,0,0},0.7f,0.03f,Color{0,60,255,255});

    std::vector<Detector> detectors;

    initDetector(detectors,mainPlayer);

    //---------------------------------------------------------------------------------------


    // Main game loop
    while (!WindowShouldClose() && !closeWindow)    // Detect window close button or ESC key
    {   

        if(curPage == MainPage){
            MainMenu(curPage,playButton,quitButton,closeWindow);            
        }

        if(curPage== GamePage){
            Gameplay(mainPlayer,sTracker,coinList,detectors,numCoins);
            if(mainPlayer.isDead())
            {
                curPage = ScorePage;
            }
        }

        if(curPage == ScorePage){
            ScoreMenu(mainPlayer,sTracker,playButton,quitButton,curPage,closeWindow,coinList,numCoins,detectors);
        }
    }

    CloseWindow();       

    return 0;
}