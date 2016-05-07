//
// Created by Schilcote on 5/5/2016.
//

#include <cstdlib>
#include <list>
#include <exception>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include "Map.h"
#include "Ant.h"

using namespace std;

//std::ostream& operator<<(std::ostream &os, const Vec3D &v) { os << "(" << v.x << ", " << v.y << ", " << v.z << ")"; return os;}

//Simply generates a uniformly random number from -1 to 1. If you use the rand() %... approach, your randomness is
//biased towards lower numbers; if you use this biased randomness to do a random walk, you'll end up in the upper left
//corner of the map every time. So we use proper random numbers.
int Ant::uniform_random_offset() {
    int reducer = RAND_MAX/3, result=0;
    while (true) {
        result = rand() / reducer;
        if (result <= 2) {
            return result - 1;
        }
    }
}

Vec3D Ant::random_direction() {
    int x=0, y=0, z=0;
    //We need actual uniform random numbers so the ants don't all just wander in to the upper left corner
    do {
        x += uniform_random_offset();
        y += uniform_random_offset();
        z += uniform_random_offset();
    } while (x == 0 && y == 0 && z == 0);
    return Vec3D(x, y, z);
}

Vec3D Ant::random_valid_move(Map & world) {
    Vec3D move;
    while (true) {
        move = random_direction();
        if (is_valid_move(move, world) && world[pos + move].empty()) {
            return move;
        }
    }
}

void Ant::think(Map & world) {
    //Random walk...
    move(random_valid_move(world), world);
    //And moving takes our whole turn.
    time-=100;

    //And then check for enemies in range.
    std::list<GameObj*>::const_iterator iterator, end;
    Vec3D rpos;
    GameObj * theobj;
    Ant* theant;
    for (int dx=-1; dx <= 1; dx++) {
        for (int dy=-1; dy <= 1; dy++) {
            for (int dz = -1; dz <= 1; dz++) {
                rpos = (get_pos() + Vec3D(dx, dy, dz));
                try { iterator = world[rpos].begin();
                    end=world[rpos].end(); }
                catch (invalid_argument& e) {
                    continue; } //if we get an exception that just means we went out of bounds; just don't check there

                for (; iterator != end; ++iterator) {
                    theobj = *iterator;
                    theant = dynamic_cast<Ant *> (theobj); //This checks if the GameObj in the list is an Ant, and if not evaluates to NULL instead
                    if (theant != NULL) {
                        if (theant->get_team() != team) { //only kill enemy ants ofc.
                            if (iterator != end) {++iterator;} //We have to move the iterator forward before killing an ant, because doing so removes it from the list.
                            theant->destroy(world);
                            cout << "Ant on team " << team << " killed ant on team " << theant->get_team() << endl;
                            //And then killing another ant also kills this ant, so there's nothing more we can do from here.
                            destroy(world); //call our own destroy()
                            return;
                        }
                    }
                }
            }
        }
    }
}

int Ant::get_team() {
    return team;
}

void Ant::set_team(int nuteam) {
    team = nuteam;
}