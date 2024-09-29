#include "scoreTracker.h"

ScoreTracker::ScoreTracker(float initTimmer)
    :playerPoints(0),timmerStart(initTimmer){timmer=timmerStart;stopTimmer=false;};

void ScoreTracker::appendPoints(){
    playerPoints += 1;
}

int ScoreTracker::getPoint() const {
    return playerPoints;
}

void ScoreTracker::reset(){
    playerPoints = 0;
    timmer = timmerStart;
    stopTimmer = false;
}

void ScoreTracker::UpdateTimmer(){
    if(stopTimmer){return;}
    timmer -= GetFrameTime();
}

    float ScoreTracker::getTimmer() const{return timmer;}

    void ScoreTracker::setTimmerStop(bool status){
        stopTimmer = status;
    }



