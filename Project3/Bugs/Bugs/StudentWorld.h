#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include <string>
#include "Field.h"
#include "Actor.h"
#include "Compiler.h"
#include<map>
#include<vector>
// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{

public:
	StudentWorld(std::string assetDir)
	 : GameWorld(assetDir)
	{
        for(int i = 0;i<4; i++)
        {
            m_antsPerTeam[i] = 0;
        }
        m_ticks = 0;
	}

	virtual int init()
	{
        
        m_ticks = 0;
        if(loadFieldAndObjects())
        {
           
            return GWSTATUS_CONTINUE_GAME;
        }
        return GWSTATUS_LEVEL_ERROR;
	}

	virtual int move()
	{
        increaseTicks();
        performDoSomethingforAllActors();
        resetPositions();
        removeDeadActors();
        
        updateStatus();
        if(isSimulationOver())
        {
            //if(WinningAntName()==-1)
                return GWSTATUS_NO_WINNER;
            //else
                
                
        }
        
        return GWSTATUS_CONTINUE_GAME;
	}

	virtual void cleanUp()
	{
        deleteActors();
        //deleteGrid();
        
	}
    ~StudentWorld()
    {
        cleanUp();
    }
    bool doesStopMovement(int x, int y);
    void createNewActor(Field::FieldItem f, int x, int y);
    void createActor(Actor*);
    void createFoodWhenDead( int x, int y);
    void performActionOnAllActorsAt(int,int,int);
    bool hasFood(int,int);
    int hasFood(int,int,int);
    void moult(int,int);
    void increaseAntNumber(int);
private:
    
    struct Coord{
        int x,y;
        bool operator<(const Coord &a) const
        {
            if(a.x == x)
                return y<a.y;
            return x<a.x;
        }
       
        Coord(int a, int b)
        {
            x=a; y=b;
        }
        
    };
    std::map<Coord,std::vector<Actor*>> m_allActors;
    
    int m_ticks;
    int m_antsPerTeam[4];
    int m_nTeams;
    
    
    int getTicks()const
    {
        return m_ticks;
    }
    //void setUpVectors();
    void resetPositions();
    void deleteActorsAtPos(int,int);
    void deleteActors();
    //bool hasNonLivingActors(int,int);
    int * getTeams() ;
    int getNumberOfAntsForAnt(int a);
    bool loadFieldAndObjects();
    void increaseTicks();
    void performDoSomethingforAllActors();
    void performDoSomethingAtPos(int,int);
    void updateStatus();
    void removeDeadActors();
    bool isSimulationOver()const;
    int WinningAntName()const;
    std::string formatDisplay(int ticks,int antsAnt0,int antsAnt1,int antsAnt2,int antsAnt3,int winningAntNumber)const;
    //void deleteGrid();
    bool checkPosChange(int oldx, int oldy, int x, int y)const;

    
};




#endif // STUDENTWORLD_H_
