//
// Created by Schilcote on 5/5/2016.
//

#ifndef FINAL_VEC3D_H
#define FINAL_VEC3D_H

#include <ostream>

//Represents a 3-dimensional cartesian vector
class Vec3D {
public:
    int x, y, z;
    Vec3D ();
    Vec3D (const Vec3D & other);
    Vec3D (int nx, int ny, int nz);
    Vec3D operator+(const Vec3D & other);
    void operator+=(const Vec3D & other);
    Vec3D operator-();
    Vec3D operator-(const Vec3D & other);
    void operator-=(const Vec3D & other);
    Vec3D operator=(const Vec3D & other);
    const bool operator== (const Vec3D & other);
};



#endif //FINAL_VEC3D_H
