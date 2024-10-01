
#include "raylib.h"
#include "player.h"
#include "coin.h"
#include "scoreTracker.h"
#include <vector>
#include "detector.h"
#include <iostream>
#include <string>
#include <sstream>





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
    const char* GameTitle = "Detect n Dash";
    int fontSize = 50;
    int textWidth = MeasureText(GameTitle, fontSize);
    int centerX = (GetScreenWidth() - textWidth) / 2;
    int centerY = (GetScreenHeight() / 2 - fontSize / 2) - 50; 
    DrawText(GameTitle, centerX, centerY, fontSize, Color{216,68,68,255});

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

void Gameplay(Player &mainPlayer,ScoreTracker &sTracker, std::vector<Coin> &coinList, std::vector<Detector> &dList, int maxCoins, std::vector<Model> enviorment)
{   
    if (!IsCursorHidden())
    {
        DisableCursor();
        // EnableCursor();
    }

    sTracker.UpdateTimmer();

        BeginDrawing();
            ClearBackground(BLACK);
    
                BeginMode3D(mainPlayer.getCamera());   

                for (int i = 0; i < enviorment.size(); i++)
                {
                    DrawModel(enviorment[i],Vector3{0,-0.5f,0},2.0f,WHITE);
                }
                


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
                

                // DrawGrid(80, 1.0f);
                
                EndMode3D();

            //UI
            DrawText(("Score: " + std::to_string(sTracker.getPoint())).c_str(), 5,30,20,GREEN);
            DrawText(("Lives: " + std::to_string(mainPlayer.getCurLives())).c_str(), 5,50,20,GREEN);
            const char* text = TextFormat("%.1f", sTracker.getTimmer());
            int textWidth = MeasureText(text, 20);
            DrawText(text, (GetScreenWidth() - textWidth) / 2, 20, 20, MAROON); 
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


void initDetector(std::vector<Detector> &dList,Player &mainPlayer, Model Skull, Model Pumk, Texture2D tex)
{
    int numMinDect = 10;
    int numMaxDect = 15;
    // Initialize the Detector objects
    for (int i = 0; i < GetRandomValue(numMinDect,numMaxDect); ++i) {
        // You can modify the initPos or other parameters based on `i` if needed
        std::vector<Vector3> initPotralPoints;
        for(int p = 0; p < GetRandomValue(5,9);p++){ //Rand number of points
            initPotralPoints.push_back(getRandV3(4.0f,30.0f)); // Position of the points
        }
        Model curModel;
        if(GetRandomValue(0,1))
        {
            curModel = Skull;
        }else{
            curModel = Pumk;
        }
        


//Refrance for Below
//float initRotation, Player &initPlayerRef,float initvDebth,
//float initvWidth,float initvAngle,std::vector<Vector3> initPotralPoints, float initpSpeed
        Detector newDetector(
            0, mainPlayer, GetRandomValue(4,7),
             GetRandomValue(4,6), GetRandomValue(50,100), initPotralPoints, getRandFloat(4,8,true),curModel,tex);
        dList.push_back(newDetector); // Add the new Detector to the vector
    }
}

void ResetGame(Player &mainPlayer, ScoreTracker &sTracker,std::vector<Coin> &coinList,int numCoins,std::vector<Detector> &dList, Model skull, Model pumk, Texture2D tex){
    //res player
    mainPlayer.Reset();
    coinList = initCoins(numCoins,sTracker);
    sTracker.reset();
    dList.clear();
    initDetector(dList,mainPlayer,skull,pumk,tex);
}

void ScoreMenu(Player &mainPlayer,ScoreTracker &sTracker,Rectangle resetButton, Rectangle quitButton,MenuPages &curPage,bool &closeWin,std::vector<Coin> &coinList,int numCoins,std::vector<Detector> &dList, Model skull, Model pumk, Texture2D tex){
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
        ResetGame(mainPlayer,sTracker,coinList,numCoins, dList, skull,pumk,tex);

    }
    if (quitHover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {   
        //TODO
        closeWin = true;
    }

    const char* mainText;
    if (sTracker.getPoint() >= numCoins)
    {
        mainText = "Congrats You Collected all the Coins";
    }else{
        mainText = TextFormat("Lookes like you missed %d coins try again?", numCoins - sTracker.getPoint() );
    }
    

    BeginDrawing();
    ClearBackground(LIGHTGRAY);
    // Define font size for the text
    int fontSize = 20;
    int textWidth = MeasureText(mainText, fontSize);
    int centerX = (GetScreenWidth() - textWidth) / 2;
    int centerY = GetScreenHeight() / 2 - fontSize / 2; // Roughly center the text vertically
    DrawText(mainText, centerX, centerY, fontSize, DARKGRAY);


    //buttons
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
    DrawText(scoreText.c_str(), 10 , GetScreenHeight() - 50, 30, DARKGRAY);

    const char* timeString = TextFormat("Timer Remaining: %.2f", sTracker.getTimmer());
    DrawText(timeString, 10 , GetScreenHeight() - 100, 30, DARKGRAY);
    
    DrawText("Quit",quitButton.x + 135,quitButton.y+5,40,DARKGRAY);

    
    EndDrawing();
}





int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 925;
    const int screenHeight = 520;

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

    //assets
    Texture2D tex = LoadTexture("Assets/halloweenbits_texture.png");
    
    Model skullModel = LoadModel("Assets/skull.obj");
    Model jackOLanternModel = LoadModel("Assets/pumpkin_orange_jackolantern.obj");
    Model ghostModel = LoadModel("Assets/Player.obj");
    
    skullModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = tex;
    jackOLanternModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = tex;
    ghostModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = tex;
  

    std::vector<Model> environmentModels;
    // Specify the range of model indices
    const int startIndex = 0;
    const int endIndex = 20; // Load models from 0 to 5 (inclusive)

    // Load models using a loop
    for (int i = startIndex; i <= endIndex; i++) {
        // Create the model file path dynamically
        std::ostringstream modelFilePath;
        modelFilePath << "Assets/Enviorment" << i << ".obj"; // Construct the file path
        environmentModels.push_back(LoadModel(modelFilePath.str().c_str()));
        environmentModels[i].materials->maps[MATERIAL_MAP_DIFFUSE].texture = tex;
    }



    //Game init
    float timeLimit = 1.5*60; //in seconds
    ScoreTracker sTracker(timeLimit);
    int numCoins = 20;
    std::vector<Coin> coinList = initCoins(numCoins,sTracker);

    Player mainPlayer (Vector3{0,0,0},0.7f,0.03f,Color{148, 146, 192,255},ghostModel,sTracker);

    std::vector<Detector> detectors;

    initDetector(detectors,mainPlayer,skullModel,jackOLanternModel,tex);



    //---------------------------------------------------------------------------------------


    // Main game loop
    while (!WindowShouldClose() && !closeWindow)    // Detect window close button or ESC key
    {   

        if(curPage == MainPage){
            MainMenu(curPage,playButton,quitButton,closeWindow);            
        }

        if(curPage== GamePage){

            Gameplay(mainPlayer,sTracker,coinList,detectors,numCoins,environmentModels);
            if(mainPlayer.isDead())
            {
                curPage = ScorePage;
            }
        }

        if(curPage == ScorePage){
            ScoreMenu(mainPlayer,sTracker,playButton,quitButton,curPage,closeWindow,coinList,numCoins,detectors,skullModel,jackOLanternModel,tex);
        }
    }

    UnloadModel(skullModel);
    UnloadModel(jackOLanternModel);
    UnloadTexture(tex);

    CloseWindow();       

    return 0;
}