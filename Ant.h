//
// Created by Schilcote on 5/5/2016.
//

#ifndef FINAL_ANT_H
#define FINAL_ANT_H

#include <random>
#include "GameObj.h"

//Represents... an ant.
class Ant: public GameObj {
private:
    int team;
    //Vec3D pos;
    int uniform_random_offset();
    Vec3D random_direction();
    Vec3D random_valid_move(Map & world);
public:
    void think(Map & world);
    void set_team(int newteam);
    int get_team();
};

#endif //FINAL_ANT_H
