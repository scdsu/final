//
// Created by Schilcote on 5/5/2016.
//

#include "Vec3D.h"
#include "Map.h"
#include "GameObj.h"

GameObj::GameObj() {
    destroyed=false;
    time=100;
}

Vec3D GameObj::get_pos(){
    return pos;
}

//Sets position and updates the world's knowledge of where we are.
void GameObj::set_pos(Vec3D newpos, Map &world) {
    //Whenever we change position, we also have to update the Map's knowledge of what is where.
    world[pos].remove(this);
    pos = newpos;
    pos.x = newpos.x;
    pos.y = newpos.y;
    pos.z = newpos.z;
    world[newpos].push_back(this);
}

//Given a relative position (direction vector), move in that direction.
void GameObj::move(Vec3D newpos, Map &world) {
    set_pos(pos + newpos, world);
}

//Returns true if this GameObj can move along the given direction vector. Will always return false for direction vectors
//where any component is outside the -1 to 1 range.
bool GameObj::is_valid_move(Vec3D move, Map & world) {
    int transition = world.get_transitions(pos);
    int x, y, z;
    x = move.x; y=move.y; z=move.z;
    //If more than one element of the move vector is nonzero...
    if ( ((x && y) || (x && z) || (y && z)) ) {
        //break it down to three checks, one for each component.
        return (is_valid_move(Vec3D(x, 0, 0), world) && is_valid_move(Vec3D(0, y, 0), world) && is_valid_move(Vec3D(0, 0, z), world));
    }

    return (
            (move == Vec3D(0, 0, 0)) ||
            (move == Vec3D(1, 0, 0) && (transition & TRANSITION_XPLUS)) ||
            (move == Vec3D(-1, 0, 0) && (transition & TRANSITION_XMINUS)) ||
            (move == Vec3D(0, 1, 0) && (transition & TRANSITION_YPLUS)) ||
            (move == Vec3D(0, -1, 0) && (transition & TRANSITION_YMINUS)) ||
            (move == Vec3D(0, 0, 1) && (transition & TRANSITION_ZPLUS)) ||
            (move == Vec3D(0, 0, -1) && (transition & TRANSITION_ZMINUS))
    );
}

//Remove this GameObj from the simulation and flag it to be deleted from memory.
void GameObj::destroy(Map &world) {
    world[pos].remove(this);
    destroyed=true; //The main loop will see this flag and free this object
}

bool GameObj::is_destroyed() {
    return destroyed;
}

//Gets the actual number of time units this GameObj has left.
//Time gets consumed by think() whenever the GameObj takes an action and when it hits zero the GameObj can take no more actions.
int GameObj::get_time_units_remaining() {
    return time;
}

//Returns true if this GameObj has time remaining and can take actions, i.e. if get_time_units_remaining() > 0
bool GameObj::has_time() { return (time > 0); }

//Give this GameObj more time. 100 is the normal amount.
void GameObj::regenerate_time(int amount/*=100*/) {
    time+=amount;
}