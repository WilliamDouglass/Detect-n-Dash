#ifndef scoreTrackerH
#define scoreTrackerH

#include <raylib.h>


class ScoreTracker
{
private:
    int playerPoints;
    float timmerStart;
    float timmer;
    bool stopTimmer;


public:
    ScoreTracker(float initTime);

    void UpdateTimmer();
    
    void appendPoints();

    void reset();

    int getPoint() const;

    float getTimmer() const;

    void setTimmerStop(bool status);


};




#endif