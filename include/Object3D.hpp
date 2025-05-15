#pragma once
#include <vector>
#include <set>
#include <stdexcept>
#include <Constraint3D.hpp>

struct Coords3DInt
{
    int x, y, z;
};

class Object3D
{
public:
    Object3D(unsigned _id = 0, double _weight = 0.0, Constraint3D _constraints = Constraint3D());
    Object3D(Coords3DInt _position);
    ~Object3D();

    Coords3DInt position;
    unsigned id;                //representa el id de la pieza 3D
    double weight;            // representa la frecuencia relativa de la pieza 3D
    Constraint3D constraints; // restricciones de la pieza 3D
};
