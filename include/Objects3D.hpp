#pragma once
#include <vector>

struct Point3Dint
{
    int x, y, z;
};

class Object3D
{
public:
    Object3D(Point3Dint _position, unsigned _id);
    Object3D(Point3Dint _position);
    ~Object3D();
    Point3Dint position;
    unsigned id;
};

Object3D::Object3D(Point3Dint _position, unsigned _id)
{
    this->position = _position;
    this->id = _id;
}
Object3D::Object3D(Point3Dint _position)
{
    this->position = _position;
    this->id = 0;
}

Object3D::~Object3D()
{
}

enum RelativeDirection
{
    ABOVE,
    BELOW,
    NORTH,
    EAST,
    SOUTH,
    WEST
};

class Constraint3D
{
public:
    Constraint3D();
    Constraint3D(std::vector<unsigned> AllowedIDsAbove,
                 std::vector<unsigned> AllowedIDsBelow,
                 std::vector<unsigned> AllowedIDsNorth,
                 std::vector<unsigned> AllowedIDsEast,
                 std::vector<unsigned> AllowedIDsSouth,
                 std::vector<unsigned> AllowedIDsWest);
    Constraint3D(Constraint3D &&) = default;
    Constraint3D(const Constraint3D &) = default;
    Constraint3D &operator=(Constraint3D &&) = default;
    Constraint3D &operator=(const Constraint3D &) = default;
    ~Constraint3D();

    std::vector<unsigned> get_constraints_for_direction(RelativeDirection direction);

private:
    std::vector<unsigned> AllowedIDsAbove;
    std::vector<unsigned> AllowedIDsBelow;
    std::vector<unsigned> AllowedIDsNorth;
    std::vector<unsigned> AllowedIDsEast;
    std::vector<unsigned> AllowedIDsSouth;
    std::vector<unsigned> AllowedIDsWest;
};

Constraint3D::Constraint3D()
{
}
std::vector<unsigned> Constraint3D::get_constraints_for_direction(RelativeDirection direction)
{
    switch (direction)
    {
    case ABOVE:
        return this->AllowedIDsAbove;
        break;
    case BELOW:
        return this->AllowedIDsBelow;
        break;
    case NORTH:
        return this->AllowedIDsNorth;
        break;
    case EAST:
        return this->AllowedIDsEast;
        break;
    case SOUTH:
        return this->AllowedIDsSouth;
        break;
    case WEST:
        return this->AllowedIDsWest;
        break;

    default:
        throw std::invalid_argument("Received Invalid Direction");
    }
}
Constraint3D::~Constraint3D()
{
}