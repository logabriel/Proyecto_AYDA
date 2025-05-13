#include <Constraint3D.hpp>
#include <stdexcept>

Constraint3D::Constraint3D()
{
}

Constraint3D::~Constraint3D()
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