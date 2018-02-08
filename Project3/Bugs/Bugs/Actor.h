#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
class StudentWorld;
class Compiler;
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Actor: public GraphObject{
    int m_hitpoints;
    bool m_alive;
    int sleepCount;
    StudentWorld *arena;
    
    
    
    
public:
    void setSleep(int);
    void setDead();
    void setHitpoints(int);
    bool isBlocked(int x, int y) const;
    
    virtual Actor& operator=(const Actor &a);
    virtual void updateHitpoints();
    Actor(StudentWorld *s,int imageID, int startX, int startY, Direction dir = right, int depth = 0);
    // Is this actor the anthill of the indicated colony?
    virtual bool isAntHill(int colony) const;
    // Is this actor an enemy of an ant of the indicated colony?
    virtual bool isEnemy(int colony) const;
    
    // Is this actor detected as dangerous by an ant of the indicated colony?
    virtual bool isDangerous(int colony) const;
    
    // Is this actor detected by an ant as a pheromone?
    virtual bool isPheromone() const;
    
    // Cause this actor to be be bitten, suffering an amount of damage.
    virtual void getBitten(int amt);
    
    // Is an enemy of an ant of the indicated colony at x,y?
    bool isEnemyAt(int x, int y, int colony) const;
    
    // Is something dangerous to an ant of the indicated colony at x,y?
    bool isDangerAt(int x, int y, int colony) const;
    
    // Is the anthill of the indicated colony at x,y?
    bool isAntHillAt(int x, int y, int colony) const;
    
    // Bite an enemy of an ant of the indicated colony at me's location
    // (other than me; insects don't bite themselves).  Return true if an
    // enemy was bitten.
    bool biteEnemyAt(Actor* me, int colony, int biteDamage);
    
    
    virtual void onDead() = 0;
    virtual void doSomething() = 0;
    bool isDead() const;
    virtual bool isLiving() = 0 ;
    int getSleepCount() const;
    int getHitpoints() const;
    void calculationsOnHitpoints(int);
    void calculationsOnSleepCount(int);
    virtual bool isAdult();
    StudentWorld* getArena()const;
    virtual bool canBlock() const;
    virtual bool isFood() const;
    virtual void poisonInsect();
    virtual void stunInsect();
    bool isNotValidCoord(int,int)const;

};






Actor::Direction getRandomDirection();





class NonLivingObject:public Actor{
public:
    virtual bool isLiving();
    NonLivingObject(StudentWorld *s,int imageID, int startX, int startY, Direction dir, int depth);
    virtual void doSomething();
    virtual void onDead();
    
    
};


class Food: public NonLivingObject{
    
public:
    Food(StudentWorld *s, int startX, int startY, bool wasInsect);
    bool isFood() const;
    
};


class Pebble: public NonLivingObject{
    
public:
     bool isPebbleorBabyGrass() ;
    Pebble(StudentWorld *s,int startX,int startY);
    virtual bool canBlock()const;
    void doSomething();
    ~Pebble();
    
    
};

class Poison:public NonLivingObject{
public:
    Poison(StudentWorld *s,int startX,int startY);
    void doSomething();
};


class Pheromone: public NonLivingObject{
public:
    Pheromone(StudentWorld *s,int startX,int startY, int colony);
    virtual bool isPheromone(int colony) const;
    
    // Increase the strength (i.e., energy) of this pheromone.
    void increaseStrength();
};

class Pool: public NonLivingObject{
public:
    Pool(StudentWorld *s,int startX,int startY);
    void doSomething();
};


class Anthill:public NonLivingObject{
    int m_hillid;
    void giveBirth();
public:
    Anthill(StudentWorld *s,int startX,int startY,int hillid,Compiler c);
    void doSomething();
};



class Insect: public Actor{
    bool m_bitten;
public:
    Insect(StudentWorld *s,int id, int x, int y, Direction Dir, int depth);
    bool isLiving();
     bool canMove(int x, int y, Direction dir);
    virtual void doSomething() = 0;
    virtual void onDead() ;
    virtual bool isAwake();
    
};



class Ant: public Insect{
    int m_hillid;
    int m_ic;
    Compiler *m_program;
public:
    Ant(StudentWorld* sw, int startX, int startY, int colony, Compiler* program, int imageID);
    virtual void doSomething();
    virtual void getBitten(int amt);
    virtual bool isEnemy(int colony) const;
    virtual bool moveForwardIfPossible();
    
};






class GrassHopper: public Insect{
    int m_distance;
public:
    int getDistance() const;
    GrassHopper(StudentWorld *s,int id, int x, int y,int depth);
    void doSomething();
    virtual bool canMoult();
    
};


class AdultGrasshopper:public GrassHopper
{
public:
    virtual void poisonInsect();
    AdultGrasshopper(StudentWorld *s,int x, int y);
    bool isAdult();
};


class BabyGrasshopper: public GrassHopper{
    
    
public:
    bool canMoult();
    
    BabyGrasshopper(StudentWorld *s,int x, int y);
};






#endif // ACTOR_H_
