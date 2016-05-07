//
// Created by Schilcote on 5/5/2016.
//

#ifndef FINAL_GAMEOBJ_H
#define FINAL_GAMEOBJ_H

#include "Vec3D.h"
#include "Map.h"

//Represents any object that actually exists in the simulation.
class GameObj{
private:
    bool destroyed;
protected:
    Vec3D pos;
    int time;
public:
    GameObj();
    Vec3D get_pos();
    void set_pos(const Vec3D newpos, Map &world);
    void move(Vec3D newpos, Map &world);
    bool is_valid_move(Vec3D move, Map & world);
    void destroy(Map & world);
    bool is_destroyed();
    virtual void think(Map & world)=0;
    int get_time_units_remaining();
    bool has_time();
    void regenerate_time(int amount=100);
};

#endif //FINAL_GAMEOBJ_H
