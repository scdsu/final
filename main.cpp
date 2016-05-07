#include <iostream>
#include <list>
#include "Vec3D.h"
#include "Map.h"
#include "GameObj.h"
#include "Ant.h"

using namespace std;

//friend func so we can send vec3Ds to stdout and such.
//Why does it have to be here when there's one in Vec3D.cpp? ¯\_(ツ)_/¯
std::ostream& operator<<(std::ostream &os, const Vec3D &v) { os << "(" << v.x << ", " << v.y << ", " << v.z << ")"; return os;}

int main() {
    Map mymap(100);
    list<Ant*> ants;
    list<GameObj*> objs;
    int turncount = 0;

    int numa, numb, total;
    cout << "Input the number of ants you want on Team 1: " << endl;
    cin >> numa;
    cout << "Input the number of ants you want on Team 2: " << endl;
    cin >> numb;
    total = numa+numb;

    for (int t=0; t < total; t++) {
        Ant * myant;
        myant = new Ant;
        myant->set_pos(Vec3D(40,20,30),mymap); //This sets the Ant's position AND puts it in the map at the correct spot
        //myant->set_team(rand() % 2);
        myant->set_team( t > numa ? 2 : 1 );
        ants.push_back(myant);
    }

    objs.assign(ants.begin(), ants.end());

    while(true) {
        cout << "Turn: " << ++turncount << endl;
        list<GameObj*>::const_iterator iterator, end;
        for ( iterator = objs.begin(), end = objs.end(); iterator != end; ++iterator) {
            GameObj * myant;
            myant = *iterator;

            if (myant->is_destroyed()) {
                //If an ant is dead, delete it, free it, and skip to the next one.
                iterator = objs.erase(iterator);
                delete myant;
                //It might be that we're at the last ant; in that case it doesn't make much sense to skip to the next
                //ant since there is none, so we instead just finish.
                if (iterator == end) { break; }
                myant = *iterator;
            }

            myant->regenerate_time();
            while (!myant-> is_destroyed() && myant->has_time()){
                myant->think(mymap);
            }
        }

        //Check if all the ants are dead or on the same team. If so, declare draw/victory.
        if (objs.empty()) {cout << "Draw!" << endl; break;}
        int lastteam=-1;
        bool sawdifferentteam=false;
        for ( iterator = objs.begin(), end = objs.end(); iterator != end; ++iterator) {
            GameObj * theobj;
            Ant * theant;
            theobj = *iterator;

            theant = dynamic_cast<Ant *> (theobj);
            if (theant == NULL) { continue; } //dynamic_cast will evaluate to NULL if theobj is not an Ant

            if ( !theant->is_destroyed() ) {
                if (lastteam != -1) {
                    if (theant->get_team() != lastteam) {sawdifferentteam=true; break;} //Encountered an ant who wasn't on the same team as the last ant; must be at least two teams
                }
                lastteam=theant->get_team();
            }
        }
        if (!sawdifferentteam) { cout << "Team " << lastteam << " wins!" << endl; break;}
    }

    return 0;
}