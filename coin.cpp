#include "coin.h"


    Coin::Coin(Vector3 aPos, ScoreTracker &aST)
    :position(aPos), st(aST){
        radius = 0.5f;
        position.y += radius + 0.5;
        coinColor = GOLD;
        collected = false;
    }

    void Coin::Update(){
    if(!collected){
            Draw();
        }
    }

    void Coin::Draw(){
        DrawSphere(position,radius,coinColor);
    }

    void Coin::Collect(){
        
        collected = true;
        st.appendPoints();
        std::cout << "Score From COllect: " << st.getPoint() << std::endl;
    }

    bool Coin::checkColission(const Player &playerRef){
        if(!collected && CheckCollisionSpheres(position,radius,playerRef.getPosition(),playerRef.getSize()))
        {
            Collect();
            return true;
        }
        return false;
        
    }
