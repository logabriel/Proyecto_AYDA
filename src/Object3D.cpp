#include <Object3D.hpp>

Object3D::Object3D(Coords3DInt _position, unsigned _id, double _weight, Constraint3D _constraints)
{
    this->position = _position;
    this->id = _id;
    this->weight = _weight;
    this->constraints = _constraints;
}

Object3D::Object3D(Coords3DInt _position)
{
    this->position = _position;
    this->id = 0;
    this->weight = 0.0;
    this->constraints = Constraint3D();
}

Object3D::~Object3D()
{
}