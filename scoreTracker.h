#ifndef scoreTrackerH
#define scoreTrackerH

#include <raylib.h>


class ScoreTracker
{
private:
    int playerPoints;


public:
    ScoreTracker();
    
    void appendPoints();

    void resetPoints();

    int getPoint() const;


};




#endif