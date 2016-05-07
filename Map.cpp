//
// Created by Schilcote on 5/5/2016.
//

#include <list>
#include <iostream>
//#include <exception>
#include <stdexcept>
#include "Vec3D.h"
#include "Map.h"

using namespace std;



Map::Map(int nsize) : size(nsize) {
    space = new std::list<GameObj*> [size * size * size];
    //The lists don't need initialization; they know they're empty

    transition = new unsigned int [size*size*size];
    //Initialize the transitions array to being open in every direction...
    for (int t=0; t < size*size*size; t++) { transition[t] = TRANSITION_ALL; }
    //... except on the edges. We don't want agents walking off the edge and crashing the game.
    for (int x=0; x < size; x++) {
        for (int y=0; y < size; y++) {
            for (int z=0; z < size; z++) {
                int idx = idx_from_vec(Vec3D(x,y,z));
                if (x == 0) {
                    transition[idx] = transition[idx] & ~TRANSITION_XMINUS;
                } else if (x == size-1) {
                    transition[idx] = transition[idx] & ~TRANSITION_XPLUS;
                }

                if (y == 0) {
                    transition[idx] = transition[idx] & ~TRANSITION_YMINUS;
                } else if (y == size-1) {
                    transition[idx] = transition[idx] & ~TRANSITION_YPLUS;
                }

                if (z == 0) {
                    transition[idx] = transition[idx] & ~TRANSITION_ZMINUS;
                } else if (z == size-1) {
                    transition[idx] = transition[idx] & ~TRANSITION_ZPLUS;
                }
            }
        }
    }
}

Map::~Map() {
    delete[] space;
    delete[] transition;
}

//Given a Vec3D, return the index into space or transition that represents that position.
unsigned int Map::idx_from_vec(Vec3D v) {
    unsigned int result;
    if (v.x >= size || v.y >= size || v.z >= size || v.x < 0 || v.y < 0 || v.z < 0) {
        throw invalid_argument("Map: Vec3D parameter to operator[] out of range");
    }
    result = (unsigned int) v.x;
    result += v.y * size;
    result += v.z * (size * size);
    return result;
}

std::list<GameObj*> & Map::operator[] (Vec3D pos) {
    return space[idx_from_vec(pos)];
}

unsigned int Map::get_transitions(Vec3D pos) {
    return transition[idx_from_vec(pos)];
}

void Map::set_transitions(Vec3D pos, unsigned int newtransitions) {
    transition[idx_from_vec(pos)] = newtransitions;
}