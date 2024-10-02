#include "coin.h"


    Coin::Coin(Vector3 aPos, ScoreTracker &aST, Model aModel)
    :position(aPos), st(aST), model(aModel){
        radius = 0.5f;
        position.y = 0;
        coinColor = GOLD;
        collected = false;
    }

    void Coin::Update(){
    if(!collected){
            Draw();
        }
    }

    void Coin::Draw(){

        // DrawSphere(position,radius,coinColor);
        // roation = st.getTimmer();
        roation += 1;
        DrawModelEx(model,position, Vector3{0,1,0},roation,Vector3One(),WHITE);
                std::cout << "Rot: " << roation << std::endl;
    }

    void Coin::Collect(){
        
        collected = true;
        st.appendPoints();
        // std::cout << "Score From COllect: " << st.getPoint() << std::endl;
    }

    bool Coin::checkColission(const Player &playerRef){
        if(playerRef.isInIFrames()){return false;}
        if(!collected && CheckCollisionSpheres(position,radius,playerRef.getPosition(),playerRef.getSize()+1))
        {   
            Collect();
            return true;
        }
        return false;
        
    }
