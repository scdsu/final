//
// Created by Schilcote on 5/5/2016.
//

#include <iostream>
#include <ostream>
#include "Vec3D.h"

Vec3D::Vec3D() { x=y=z=0; }
Vec3D::Vec3D(const Vec3D & other) { x=other.x; y=other.y; z=other.z; }
Vec3D::Vec3D (int nx, int ny, int nz) { x = nx; y = ny; z = nz; };
Vec3D Vec3D::operator+(const Vec3D & other) { return Vec3D(x + other.x, y + other.y, z + other.z); }
void Vec3D::operator+=(const Vec3D & other) { x += other.x; y += other.y; z += other.z; }
Vec3D Vec3D::operator-() {return Vec3D(-x, -y, -z); }
Vec3D Vec3D::operator-(const Vec3D & other) {return Vec3D(x - other.x, y - other.y, z - other.z); }
void Vec3D::operator-=(const Vec3D & other) { x -= other.x; y -= other.y; z -= other.z; }
Vec3D Vec3D::operator=(const Vec3D & other) { x=other.x; y=other.y; z=other.z; return *this;}
const bool Vec3D::operator==(const Vec3D & other) { return (x == other.x && y == other.y && z == other.z); }

//friend func so we can send vec3Ds to stdout and such
//std::ostream& operator<<(std::ostream &os, const Vec3D &v) { os << "(" << v.x << ", " << v.y << ", " << v.z << ")"; return os;}