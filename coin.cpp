#include "coin.h"

    Coin::Coin(Vector3 aPos, ScoreTracker aST)
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
    }

    bool Coin::checkColission(const Player &playerRef){
        if(collected){return false;}
        float dist = Vector3Distance(position,playerRef.getPosition());
        if (dist <= radius + playerRef.getSize())
        {   
            Collect();
            return true;
        }
        return false;
        
    }
