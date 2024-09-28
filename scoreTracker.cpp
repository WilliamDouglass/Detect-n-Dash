#include "scoreTracker.h"

ScoreTracker::ScoreTracker()
    :playerPoints(0){};

void ScoreTracker::appendPoints(){
    playerPoints += 1;
}

int ScoreTracker::getPoint() const {
    return playerPoints;
}

