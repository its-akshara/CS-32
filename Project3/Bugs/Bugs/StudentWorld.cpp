
#include "StudentWorld.h"
#include <string>
#include <iomanip>
#include<sstream>
#include<iostream>
using namespace std;







GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

bool StudentWorld::doesStopMovement(int x, int y)
{
    
    Coord curr(x,y);
    if(m_allActors.find(curr) == m_allActors.end())
        return false;
    for(int i = 0; i<m_allActors[curr].size(); i++)
    {
        vector<Actor *>::iterator it = m_allActors[curr].begin() + i;
       if((*it)->canBlock())
           return true;
        
    }
    return false;
}

void StudentWorld::increaseAntNumber(int field)
{
    m_antsPerTeam[field-1]++;
}

/*bool StudentWorld::hasNonLivingActors(int x, int y)  //
{
    Coord curr(x,y);
    if(m_allActors.find(curr) == m_allActors.end())
        return false;
    for(int i = 0; i<m_allActors[curr].size(); i++)
    {
        vector<Actor *>::iterator it = m_allActors[curr].begin() + i;
        if(!(*it)->isLiving())
        {
           return true; 
        }
        
    }
    return false;
}*/
 bool StudentWorld::loadFieldAndObjects()
{
    Field f;
    string fieldFile = getFieldFilename();
    
    string error;
    if (f.loadField(fieldFile, error) != Field::LoadResult::load_success)
    {
        setError(fieldFile + " " + error);
        return false; // something bad happened!
    }
    Compiler *compilerForEntrant0, *compilerForEntrant1,
    *compilerForEntrant2, *compilerForEntrant3;
    Anthill *ah0, *ah1, *ah2, *ah3;
    // get the names of all of the ant program source files
    // we provide the getFilenamesOfAntPrograms() function for
    // you in our GameWorld class.
    std::vector<std::string> fileNames = getFilenamesOfAntPrograms();
    compilerForEntrant0 = new Compiler;
    //std::string error;
    // compile the source file… If the compile function returns
    // false, there was a syntax error during compilation!
    if ( ! compilerForEntrant0->compile(fileNames[0], error) )
        
    {
        // entrant 0’s source code had a syntax error!
        // send this error to our framework to warn the user.
        // do it JUST like this!
        setError(fileNames[0] + " " + error);
    }
    // otherwise, the entrant’s file compiled correctly!
    // now allocate our first anthill object and make sure it has
    // a pointer to the Compiler object for ant type #0,
    // so it can determine what set of instructions to use to control
    // ants in colony #0.
    // You have to figure out what to put for ... in the line below.
    //ah0 = new Anthill(..., compilerForEntrant0);
    // now add our new anthill object to our simulation data
    // structure so it can be tracked and asked to do something by
    // our virtual world during each tick of the simulation
    //addObjectToSimulation(ah0);
    for(int i = 0; i<VIEW_HEIGHT;i++ )
    {
        for(int j = 0; j<VIEW_WIDTH; j++)
        {
            Field::FieldItem item = f.getContentsOf(i,j);
            //Time to add item
            //if(item == Field::grasshopper || item == Field::rock)
            if(item==Field::anthill0)
            {
                
            }
            
            createNewActor(item, i, j);
              /*  switch(item)
            {
                
                case Field::empty:
                    break;
                case Field::anthill0:
                    
                    break;
                case Field::anthill1:
                    break;
                case Field::anthill2:
                    break;
                case Field::anthill3:
                    break;
                    
                case Field::food:
                    Actor *a = new Food(this,j,i,false);
                    break;
                    
                case Field::grasshopper:
                    
                    Actor *a = new BabyGrasshopper(this,j,i);
                    
                    break;
                    
                case Field::water:
                    Actor *a = new Pool(this,j,i);
                    break;
                case Field::rock:
                    Actor *a = new Pebble(this,j,i);
                    break;
                case Field::poison:
                    Actor *a = new Poison(this,j,i);
                    break;
                    
                 
            }*/
        }
    }
    
    return true;
}


// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp
bool StudentWorld::hasFood(int x, int y)
{
    Coord curr(x,y);
    if(m_allActors.find(curr) == m_allActors.end())
        return false;
    for(int i = 0; i<m_allActors[curr].size(); i++)
    {
        vector<Actor *>::iterator it = m_allActors[curr].begin() + i;
        if((*it)->isFood())
        {
                (*it)->calculationsOnHitpoints(-100);
            (*it)->setDead();
            return true;
        }
        
        
    }
    return false;
}

void StudentWorld::moult(int x, int y)
{
    Coord location(x,y);
    m_allActors[location].push_back(new AdultGrasshopper(this,x,y));
    
}

int StudentWorld::hasFood(int x, int y, int field)
{
    Coord curr(x,y);
    if(m_allActors.find(curr) == m_allActors.end())
        return -1;
    for(int i = 0; i<m_allActors[curr].size(); i++)
    {
        vector<Actor *>::iterator it = m_allActors[curr].begin() + i;
        if((*it)->isFood())
        {
            switch(field)
            {
                case Field::empty://anthill
                    if((*it)->getHitpoints()>10000)
                    {
                        (*it)->calculationsOnHitpoints(10000);
                        return 10000;
                    }
                    else
                    {
                        int x = (*it)->getHitpoints();
                        (*it)->calculationsOnHitpoints((*it)->getHitpoints());
                        (*it)->setDead();
                        return x;
                    }
                    //return ;
                    break;
                case Field::grasshopper:
                    if((*it)->getHitpoints()>100)
                    {
                        (*it)->calculationsOnHitpoints(100);
                        return 100;
                    }
                    else
                    {
                        int x = (*it)->getHitpoints();
                        (*it)->calculationsOnHitpoints((*it)->getHitpoints());
                        (*it)->setDead();
                        return x;
                    }
                    
                    break;
                case Field::anthill0:case Field::anthill1:case Field::anthill2:case Field::anthill3:
                    
                    break;
            }
            
            
        }
        
        
    }
    return -1;
    
}

void StudentWorld::increaseTicks()
{
    m_ticks++;
}

int * StudentWorld::getTeams()
{
    return m_antsPerTeam;
}

void StudentWorld::performDoSomethingforAllActors()
{
    map<Coord,vector<Actor*>>::iterator it;
    for(it = m_allActors
        .begin(); it!=m_allActors.end();it++ )
    {
        Coord c = (*it).first;
        performDoSomethingAtPos(c.x, c.y);
    }
}
/*bool StudentWorld:: checkPosChange(int oldx, int oldy, int x, int y)const
{
    return (oldx != x || oldy != y);
}*/
void StudentWorld::performDoSomethingAtPos(int i, int j)
{
    Coord location(i,j);
    if(m_allActors.find(location) == m_allActors.end() || m_allActors[location].empty())
        return;
    map<Coord,vector<Actor*>>::iterator it = m_allActors.find(location);
    
    
    for(int i = 0;i<(*it).second.size()    ;i++)
    {
        vector<Actor*>::iterator place =(*it).second.begin()+i;
        (*place)->doSomething();
    }

}

void StudentWorld::resetPositions()
{
   map<Coord, vector<Actor*>>::iterator overall = m_allActors.begin();
    
    for(;overall!=m_allActors.end();overall++)
    {
        vector<Actor*>::iterator it = (*overall).second.begin();
        
        for(;it!=(*overall).second.end();)
        {
            if(*it==nullptr)
                continue;
            int x = (*it)->getX(), y = (*it)->getY();
            if(x!=overall->first.x || y!=overall->first.y){
                Coord c(x,y);
                Actor *a=(*it);
                m_allActors[c].push_back(a);
                it=(*overall).second.erase(it);
        }
            else
                it++;
        
        
           }
    }
}

int StudentWorld::getNumberOfAntsForAnt(int a)
{
    return m_antsPerTeam[a];
}

string StudentWorld:: formatDisplay(int ticks,
              int antsAnt0,
              int antsAnt1,
              int antsAnt2,
              int antsAnt3,
              int winningAntNumber
              )const
{
    
    ostringstream oss;
    oss<<"Ticks:";
    oss << setw(5)<<2000-getTicks();
    oss<<" - ";
    
    string res = oss.str();
    return res;
}


void StudentWorld::updateStatus()
{
    int ticks = getTicks();
    int antsAnt0, antsAnt1, antsAnt2, antsAnt3;
    int winningAntNumber;
    antsAnt0 = getNumberOfAntsForAnt(0);
    antsAnt1 = getNumberOfAntsForAnt(1);
    antsAnt2 = getNumberOfAntsForAnt(2);
    antsAnt3 = getNumberOfAntsForAnt(3);
    winningAntNumber = WinningAntName();
    
    // Ticks: 1134 - AmyAnt: 32 BillyAnt: 33 SuzieAnt*: 77 IgorAnt: 05
    string s = formatDisplay(ticks,antsAnt0,antsAnt1,antsAnt2,antsAnt3,winningAntNumber);
   
    setGameStatText(s);
    
}

void StudentWorld::performActionOnAllActorsAt(int x,int y,int id)
{
    Coord curr(x,y);
    if(m_allActors.find(curr) == m_allActors.end())
        return;
    for(int i = 0; i<m_allActors[curr].size(); i++)
    {
        vector<Actor *>::iterator it = m_allActors[curr].begin() + i;
        if((*it)->isLiving())
        {
            switch (id) {
                case Field::poison:
                    (*it)->poisonInsect();
                    break;
                    
                case Field::water:
                    (*it)->stunInsect();
                    break;
            }
            
            
            
            (*it)->poisonInsect();
            
        }
        
        
    }
    return ;
}

void StudentWorld::removeDeadActors()
{
    map<Coord, vector<Actor*>> :: iterator help = m_allActors.begin();
    for(int i = 0; i<m_allActors.size(); i++)
    {
        Coord current = help->first;
        for(int j = 0; j<m_allActors[current].size();j++)
        {
            vector<Actor*>::iterator okay = m_allActors[current].begin() + j;
            if((*okay)->isDead())
            {
                delete (*okay);
                m_allActors[current].erase(okay);
            }
        }
        
         map<Coord, vector<Actor*>> :: iterator checker = help;
        
        help++;
    if(m_allActors[current].empty())
        {
            m_allActors.erase(checker);
        }
    }
    
    
    }
bool StudentWorld::isSimulationOver()const
{
    return m_ticks>=2000;
}
int StudentWorld::WinningAntName()const
{
    int max = m_antsPerTeam[0];
    int mno = 0;
    for(int i = 0; i<m_nTeams;i++)
    {
        if(m_antsPerTeam[i]>max)
        {
            max = m_antsPerTeam[i];
            mno=i;
        }
        if(m_antsPerTeam[i]==max)
            return -1;
    }//who gets max first
    return mno;
}

void StudentWorld::createNewActor(Field::FieldItem f, int x, int y)
{
    Coord location(x,y);
    
    
    switch(f)
    {
        case Field::empty:
            break;
        case Field::anthill0:
            
            break;
        case Field::anthill1:
            break;
        case Field::anthill2:
            break;
        case Field::anthill3:
            break;
        
        case Field::food:
            m_allActors[location].push_back(new Food(this,y,x,false));
            break;
        case Field::grasshopper:
          
             m_allActors[location].push_back(new BabyGrasshopper(this,y,x));
         
            break;
        case Field::water:
            m_allActors[location].push_back(new Pool(this,y,x));
            break;
        case Field::rock:
            m_allActors[location].push_back(new Pebble(this,y,x));
            break;
        case Field::poison:
            m_allActors[location].push_back(new Poison(this,y,x));
            break;
    
    }
     
}

void StudentWorld::createActor(Actor *a)
{
    Coord location(a->getX(),a->getY());
    m_allActors[location].push_back(a);
}

void StudentWorld::createFoodWhenDead(int x, int y)
{
    Coord location(x,y);
    if(!hasFood(x, y))
        m_allActors[location].push_back(new Food(this,x,y,true));
}
void StudentWorld::deleteActors(){
    
    
    map<Coord, vector<Actor*>> :: iterator help = m_allActors.begin();
    for(; help!=m_allActors.end(); )
    {
        Coord current = help->first;
        deleteActorsAtPos(current.x, current.y);
        help++;
    }
    
  

}
void StudentWorld::deleteActorsAtPos(int i, int j)
{
    Coord curr(i,j);
    for(int x = 0; x<m_allActors[curr].size(); x++)
    {
        vector<Actor *>::iterator it = m_allActors[curr].begin() + x;
        delete (*it);
    }
    
    m_allActors[curr].clear();
    
   
     
     
}

