#pragma once
#include <vector>
#include <set>
#include <stdexcept>
#include <Constraint3D.hpp>

struct Point3Dint
{
    int x, y, z;
};

class Object3D
{
public:
    Object3D(Point3Dint _position, unsigned _id, double _wheight, Constraint3D _constraints);
    Object3D(Point3Dint _position);
    ~Object3D();

    Point3Dint position;
    unsigned id;
    double wheight; // representa la frecuencia relativa de la pieza 3D
    Constraint3D constraints; // restricciones de la pieza 3D
};
