#include "scoreTracker.h"

ScoreTracker::ScoreTracker()
    :playerPoints(0){};

void ScoreTracker::appendPoints(){
    playerPoints++;
}

int ScoreTracker::getPoint() const {
    return playerPoints;
}

