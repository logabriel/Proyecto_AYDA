#include <Object3D.hpp>

Object3D::Object3D(Point3Dint _position, unsigned _id, double _wheight, Constraint3D _constraints)
{
    this->position = _position;
    this->id = _id;
    this->wheight = _wheight;
    this->constraints = _constraints;
}

Object3D::Object3D(Point3Dint _position)
{
    this->position = _position;
    this->id = 0;
    this->wheight = 0.0;
    this->constraints = Constraint3D();
}

Object3D::~Object3D()
{
}