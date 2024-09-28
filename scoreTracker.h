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

    int getPoint() const;

};




#endif