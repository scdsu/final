//
// Created by Schilcote on 5/5/2016.
//

#ifndef FINAL_MAP_H
#define FINAL_MAP_H

#include <list>
#include "Vec3D.h"

//Bitmasks for representing what moves are possible from a given location in the transition map
const unsigned int TRANSITION_NONE   = 0;
const unsigned int TRANSITION_XPLUS  = 1;
const unsigned int TRANSITION_XMINUS = 2;
const unsigned int TRANSITION_YPLUS  = 4;
const unsigned int TRANSITION_YMINUS = 8;
const unsigned int TRANSITION_ZPLUS  = 16;
const unsigned int TRANSITION_ZMINUS = 32;
const unsigned int TRANSITION_ALL = TRANSITION_XMINUS | TRANSITION_XPLUS | TRANSITION_YMINUS | TRANSITION_YPLUS | TRANSITION_ZMINUS | TRANSITION_ZPLUS;

class GameObj; //Just an assurance to the compiler that there WILL be such a thing as a GameObj defined some time in the future.
//The compiler doesn't need to know anything ABOUT GameObj-s yet, since we only discuss pointers to them.

//Represents physical space in the simulation. Acts as a mapping from Vec3Ds to vectors of objects that are at that position.
//Also can give the possible moves from a given position. The volume of a Map must be less than 1624.
class Map {
private:
    const int size;
    std::list<GameObj*> * space;
    unsigned int * transition;
    unsigned int idx_from_vec(Vec3D);
public:
    Map(int nsize);
    ~Map();
    std::list<GameObj*> & operator[] (Vec3D pos);
    unsigned int get_transitions(Vec3D pos);
    void set_transitions(Vec3D pos, unsigned int newtransitions);
};

#endif //FINAL_MAP_H
