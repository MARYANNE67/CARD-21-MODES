// CardGameAdapter.h - class definition for adapter


//Ibeh Mary-Anne
//20-03-2023

#ifndef _CARDGAMEADAPTER_H_
#define _CARDGAMEADAPTER_H_

enum class GameMode
{
    HighDefinition,
    LowDefinition
};

class CardGameAdapter
{
public:
    virtual void run() {};// pure virtual
    virtual void setMode(int) {};// pure virtual
     ~CardGameAdapter(){};
};

#endif //_CARDGAMEADAPTER_H_