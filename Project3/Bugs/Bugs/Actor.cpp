#include "Actor.h"
#include "StudentWorld.h"
#include "Compiler.h"

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp
Actor::Direction getRandomDirection()
{
    return static_cast<Actor::Direction>(randInt(1,4));
}





//Actor definition:
Actor::Actor(StudentWorld *s, int imageID, int startX, int startY, Direction dir, int depth):GraphObject(imageID,startX,startY,dir,depth){
    
    arena = s;
    sleepCount = 0;
    m_alive = true;
    m_hitpoints = 500;
}
 Actor& Actor::operator=(const Actor &a)
{
    if(&a!=this)
    {
        m_hitpoints = a.m_hitpoints;
        m_alive = a.m_alive;
        arena = a.arena;
        sleepCount = a.sleepCount;
    }
    return *this;
}
bool Actor::isAntHill(int colony)const
{
    return false;
}
bool Actor::isEnemy(int colony)const
{
    return false;
}
bool Actor::canBlock()const
{
    return false;
}
bool Actor::isPheromone() const
{
    return false;
}
bool Actor::isAdult()
{
    return false;
}
bool Actor::isFood()const
{
    return false;
}
void Actor::getBitten(int amt)
{
    //
}
bool Actor::isEnemyAt(int x, int y, int colony) const
{
    return false;
}
bool Actor::isDangerAt(int x, int y, int colony) const
{
    return false;
}
void Actor::updateHitpoints(){
    
    calculationsOnHitpoints(1);
}
bool Actor::isNotValidCoord(int x, int y)const
{
    return x<0 || y<0 || x>=VIEW_HEIGHT || y>=VIEW_WIDTH;
}
bool Actor::isDangerous(int colony)const
{
    return false;
}
void Actor::setHitpoints(int x)
{
    m_hitpoints = x;
}
void Actor::setSleep(int x)
{
    sleepCount = x;
}

void Actor::calculationsOnHitpoints(int pt)
{
    m_hitpoints-=pt;
    if(m_hitpoints<=0)
        setDead();
}
void Actor::poisonInsect()
{
    calculationsOnHitpoints(150);
}
void Actor::stunInsect()
{
    setSleep(2);
}
void Actor::setDead()
{
    m_alive = false;
}
bool Actor::isDead()const
{
    return !m_alive;
}


int Actor::getSleepCount()const
{
    return sleepCount;
}

int Actor::getHitpoints()const
{
    return m_hitpoints;
}
StudentWorld* Actor::getArena()const
{
    return arena;
}
void Actor::calculationsOnSleepCount(int x)
{
    sleepCount-=x;
}
bool Actor::isBlocked(int x, int y)const
{
    return arena->doesStopMovement(x,y);
    
}
// Bite an enemy of an ant of the indicated colony at me's location
// (other than me; insects don't bite themselves).  Return true if an
// enemy was bitten.
bool Actor::biteEnemyAt(Actor* me, int colony, int biteDamage)
{
    return false;
}





bool NonLivingObject::isLiving()
{
    return false;
}
NonLivingObject::NonLivingObject(StudentWorld *s,int imageID, int startX, int startY, Direction dir, int depth):Actor( s,imageID, startX, startY, dir,depth)
{
    
}
void NonLivingObject::onDead()
{
    
}
void NonLivingObject::doSomething()
{
    //getArena()->performActionOnAllActorsAt(getX(),getY());
    
}

 
//Pheromone::Pheromone(StudentWorld *s,int startX,int startY, int colony):NonLivingObject(s,,startX,startY,right, 2)
//{
    
//}



Food::Food(StudentWorld *s,int startX,int startY, bool wasDead = false):NonLivingObject(s,IID_FOOD,startX,startY,right,2)
{
    if(wasDead)
        setHitpoints(100);
    else
        setHitpoints(6000);
}
bool Food::isFood()const
{
    return true;
}




Pebble::Pebble(StudentWorld *s,int startX,int startY):NonLivingObject(s,IID_ROCK,startX,startY,right,1)
{
    
}

void Pebble::doSomething()
{
    
}

Pebble::~Pebble()
{
    
}
bool Pebble::canBlock()const
{
    return true;
}




Poison::Poison(StudentWorld *s,int startX,int startY):NonLivingObject(s,IID_POISON,startX,startY,right,2)
{
    
}
void Poison::doSomething()
{
    getArena()->performActionOnAllActorsAt(getX(),getY(),Field::poison);
}






Pool::Pool(StudentWorld *s,int startX,int startY):NonLivingObject(s,IID_WATER_POOL,startX,startY,right,2)
{
    
}
void Pool::doSomething()
{
    getArena()->performActionOnAllActorsAt(getX(),getY(),Field::water);
}





Anthill::Anthill(StudentWorld *s,int startX,int startY,int hillid, Compiler c):NonLivingObject(s,IID_ANT_HILL,startX,startY,right,2)
{
    setHitpoints(8999);
    m_hillid = hillid;
}

void Anthill::doSomething()
{
    updateHitpoints();
    if(getHitpoints()<=0)
    {
        setDead();
        return;
    }
    int x = getArena()->hasFood(getX(), getY(), Field::empty);
    if(x!=-1)
    {
        calculationsOnHitpoints(-x);
        return;
    }
    if(getHitpoints()>2000)
    {
        calculationsOnHitpoints(1500);
        getArena()->increaseAntNumber(m_hillid);
    }
    
}
void Anthill::giveBirth()
{
    
}





Insect::Insect(StudentWorld *s,int id, int x, int y, Direction Dir, int depth):Actor(s,id, x, y, Dir,depth)
{
    m_bitten = false;
}
bool Insect::isLiving()
{
    return true;
}
bool Insect::isAwake()
{
    if(getSleepCount()>0)
        return false;
    return true;
}

bool Insect::canMove(int x, int y, Direction dir)
{
    
    int finalX=x,finalY=y;
    switch(dir)
    {
        case none: return true;
            break;
        case up:
            finalY--;
            break;
        case  right:
            finalX++;
            break;
        case  down:
            
            finalY++;
            break;
        case  left:
            
            finalX--;
            break;
    }
    if(isNotValidCoord(finalX,finalY))
        return false;
    if(getArena()->doesStopMovement(finalX,finalY))
        return false;
    moveTo(finalX, finalY);
    return true;
}
void Insect::onDead(){
    getArena()->createFoodWhenDead(getX(), getY());
}







Ant::Ant(StudentWorld* sw, int startX, int startY, int colony, Compiler* program, int imageID):Insect(sw, imageID, startX, startY, getRandomDirection(), 1)
{
    m_ic = 0;
    m_program = program;
}

void Ant::doSomething()
{
    
}
void Ant::getBitten(int amt)
{
    
}
 bool Ant::isEnemy(int colony) const{
     return false;
}
bool Ant::moveForwardIfPossible()
{
    return false;
}

GrassHopper::GrassHopper(StudentWorld *s,int id, int x, int y,int depth):Insect(s,id,x,y,getRandomDirection(),depth)
{
    m_distance = randInt(2, 10);
   
}

bool GrassHopper::canMoult()
{
    return false;
}
int GrassHopper::getDistance() const
{
    return m_distance;
}

void GrassHopper::doSomething()
{
   
    updateHitpoints();
    if(getHitpoints()<=0)
    {
        onDead();
        setDead();
        return;
    }
    if(!isAwake())
    {
        calculationsOnSleepCount(1);
        return;
    }
    if(isAdult())
    {
        //bite
        //jump
    }
    else //baby
    {
        if(canMoult())
        {
            getArena()->moult(getX(),getY());
            setDead();
            return;
        }
    }
    
    //eat
    int x = getArena()->hasFood(getX(), getY(), Field::grasshopper);
    if(x!=-1)
    {
        calculationsOnHitpoints(-x);
        if(randInt(1,2) == 1)
        {
            setSleep(2);
            return;
        }
        
    }
    
    if(m_distance<=0)
    {
        m_distance = randInt(2, 10);
        setDirection(getRandomDirection());
    }
    //while(canMove( getX(),getY(), getDirection() ))
    //{
        
    //}
    if(canMove( getX(),getY(), getDirection() ))
    {
         m_distance--;
    }
    else{
        m_distance = 0;
    }
    setSleep(2);
    
   
    
}


AdultGrasshopper::AdultGrasshopper(StudentWorld *s,int x, int y):GrassHopper(s,IID_ADULT_GRASSHOPPER,x,y,1)
{
    setHitpoints(1600);
}
void AdultGrasshopper::poisonInsect()
{
    
}
bool AdultGrasshopper::isAdult()
{
    return true;
}



BabyGrasshopper::BabyGrasshopper(StudentWorld *s,int x, int y):GrassHopper(s,IID_BABY_GRASSHOPPER,x,y,2)
{
    
}


bool BabyGrasshopper::canMoult()
{
    return getHitpoints()>=1600;
}





