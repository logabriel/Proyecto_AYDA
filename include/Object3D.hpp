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
    Object3D(Coords3DInt _position, unsigned _id, double _weight, Constraint3D _constraints);
    Object3D(Coords3DInt _position);
    ~Object3D();

    Coords3DInt position;
    unsigned id;
    double weight;            // representa la frecuencia relativa de la pieza 3D
    Constraint3D constraints; // restricciones de la pieza 3D
};
