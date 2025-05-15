#include <Object3D.hpp>

Object3D::Object3D(unsigned _id, double _weight, Constraint3D _constraints)
{
    position = {0, 0, 0};
    id = _id;
    weight = _weight;
    constraints = _constraints;
}

Object3D::Object3D(Coords3DInt _position)
    : position(_position), id(0), weight(0.0), constraints() 
{
}

Object3D::~Object3D()
{
}